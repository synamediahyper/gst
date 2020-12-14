/* GStreamer
 * Copyright (C) 2018, Collabora Ltd.
 * Copyright (C) 2018, SK Telecom, Co., Ltd.
 *   Author: Jeongseok Kim <jeongseok.kim@sk.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* Needed for GValueArray */
#define GLIB_DISABLE_DEPRECATION_WARNINGS

#include "gstsrtobject.h"

#include <gst/base/gstbasesink.h>
#include <gio/gnetworking.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

GST_DEBUG_CATEGORY_EXTERN (gst_debug_srtobject);
#define GST_CAT_DEFAULT gst_debug_srtobject

enum
{
  PROP_URI = 1,
  PROP_MODE,
  PROP_LOCALADDRESS,
  PROP_LOCALPORT,
  PROP_PASSPHRASE,
  PROP_PBKEYLEN,
  PROP_POLL_TIMEOUT,
  PROP_LATENCY,
  PROP_MSG_SIZE,
  PROP_STATS,
  PROP_WAIT_FOR_CONNECTION,
  PROP_STREAMID,
  PROP_LAST
};

typedef struct
{
  SRTSOCKET sock;
  gint poll_id;
  GSocketAddress *sockaddr;
  gboolean sent_headers;
} SRTCaller;

static GstStructure *gst_srt_object_accumulate_stats (GstSRTObject * srtobject,
    SRTSOCKET srtsock);

static SRTCaller *
srt_caller_new (void)
{
  SRTCaller *caller = g_new0 (SRTCaller, 1);
  caller->sock = SRT_INVALID_SOCK;
  caller->poll_id = SRT_ERROR;
  caller->sent_headers = FALSE;

  return caller;
}

static void
srt_caller_free (SRTCaller * caller)
{
  g_return_if_fail (caller != NULL);

  g_clear_object (&caller->sockaddr);

  if (caller->sock != SRT_INVALID_SOCK) {
    srt_close (caller->sock);
  }

  if (caller->poll_id != SRT_ERROR) {
    srt_epoll_release (caller->poll_id);
  }

  g_free (caller);
}

/* called with sock_lock */
static void
srt_caller_signal_removed (SRTCaller * caller, GstSRTObject * srtobject)
{
  GstStructure *stats;

  stats = gst_srt_object_accumulate_stats (srtobject, caller->sock);

  /* FIXME: These are the final statistics for the caller before we close its
   * socket. Deliver the stats to the app before we throw them away. */
  gst_structure_free (stats);

  g_signal_emit_by_name (srtobject->element, "caller-removed", caller->sock,
      caller->sockaddr);
}

struct srt_constant_params
{
  const gchar *name;
  SRT_SOCKOPT param;
  const void *val;
  int val_len;
};

static const bool bool_false = false;
static const bool bool_true = true;
static const struct linger no_linger = { 0, 0 };

/* *INDENT-OFF* */
static const struct srt_constant_params srt_params[] = {
  {"SRTO_SNDSYN",    SRTO_SNDSYN,    &bool_false, sizeof bool_false}, /* non-blocking */
  {"SRTO_RCVSYN",    SRTO_RCVSYN,    &bool_false, sizeof bool_false}, /* non-blocking */
  {"SRTO_LINGER",    SRTO_LINGER,    &no_linger,  sizeof no_linger},  /* no linger time */
  {"SRTO_TSBPDMODE", SRTO_TSBPDMODE, &bool_true,  sizeof bool_true},  /* Timestamp-based Packet Delivery mode must be enabled */
  {NULL, -1, NULL, 0},
};
/* *INDENT-ON* */

static gint srt_init_refcount = 0;

static GSocketAddress *
gst_srt_object_resolve (GstSRTObject * srtobject, const gchar * address,
    guint port, GCancellable * cancellable, GError ** err_out)
{
  GError *err = NULL;
  GSocketAddress *saddr;
  GResolver *resolver;

  saddr = g_inet_socket_address_new_from_string (address, port);
  if (!saddr) {
    GList *results;

    GST_DEBUG_OBJECT (srtobject->element, "resolving IP address for host %s",
        address);
    resolver = g_resolver_get_default ();
    results = g_resolver_lookup_by_name (resolver, address, cancellable, &err);
    if (!results)
      goto name_resolve;

    saddr = g_inet_socket_address_new (G_INET_ADDRESS (results->data), port);

    g_resolver_free_addresses (results);
    g_object_unref (resolver);
  }
#ifndef GST_DISABLE_GST_DEBUG
  {
    gchar *ip =
        g_inet_address_to_string (g_inet_socket_address_get_address
        (G_INET_SOCKET_ADDRESS (saddr)));

    GST_DEBUG_OBJECT (srtobject->element, "IP address for host %s is %s",
        address, ip);
    g_free (ip);
  }
#endif

  return saddr;

name_resolve:
  {
    GST_WARNING_OBJECT (srtobject->element, "Failed to resolve %s: %s", address,
        err->message);
    g_set_error (err_out, GST_RESOURCE_ERROR, GST_RESOURCE_ERROR_OPEN_READ,
        "Failed to resolve host '%s': %s", address, err->message);
    g_clear_error (&err);
    g_object_unref (resolver);
    return NULL;
  }
}

static gboolean
gst_srt_object_set_common_params (SRTSOCKET sock, GstSRTObject * srtobject,
    GError ** error)
{
  const struct srt_constant_params *params = srt_params;
  const gchar *passphrase;

  GST_OBJECT_LOCK (srtobject->element);

  for (; params->name != NULL; params++) {
    if (srt_setsockopt (sock, 0, params->param, params->val, params->val_len)) {
      g_set_error (error, GST_LIBRARY_ERROR, GST_LIBRARY_ERROR_SETTINGS,
          "failed to set %s (reason: %s)", params->name,
          srt_getlasterror_str ());
      goto err;
    }
  }

  passphrase = gst_structure_get_string (srtobject->parameters, "passphrase");
  if (passphrase != NULL && passphrase[0] != '\0') {
    int32_t pbkeylen;

    if (srt_setsockopt (sock, 0, SRTO_PASSPHRASE, passphrase,
            strlen (passphrase))) {
      g_set_error (error, GST_LIBRARY_ERROR, GST_LIBRARY_ERROR_SETTINGS,
          "failed to set passphrase (reason: %s)", srt_getlasterror_str ());

      goto err;
    }

    if (!gst_structure_get_int (srtobject->parameters, "pbkeylen", &pbkeylen)) {
      pbkeylen = GST_SRT_DEFAULT_PBKEYLEN;
    }

    if (srt_setsockopt (sock, 0, SRTO_PBKEYLEN, &pbkeylen, sizeof pbkeylen)) {
      g_set_error (error, GST_LIBRARY_ERROR, GST_LIBRARY_ERROR_SETTINGS,
          "failed to set pbkeylen (reason: %s)", srt_getlasterror_str ());
      goto err;
    }
  }

  {
    int32_t latency;

    if (!gst_structure_get_int (srtobject->parameters, "latency", &latency))
      latency = GST_SRT_DEFAULT_LATENCY;
    if (srt_setsockopt (sock, 0, SRTO_LATENCY, &latency, sizeof latency)) {
      g_set_error (error, GST_LIBRARY_ERROR, GST_LIBRARY_ERROR_SETTINGS,
          "failed to set latency (reason: %s)", srt_getlasterror_str ());
      goto err;
    }
  }

  if (gst_structure_has_field (srtobject->parameters, "streamid")) {
    const gchar *streamid;

    streamid = gst_structure_get_string (srtobject->parameters, "streamid");
    if (streamid != NULL && streamid[0] != '\0') {
      if (srt_setsockopt (sock, 0, SRTO_STREAMID, streamid, strlen (streamid))) {
        g_set_error (error, GST_LIBRARY_ERROR, GST_LIBRARY_ERROR_SETTINGS,
            "failed to set stream ID (reason: %s)", srt_getlasterror_str ());
      }
    }
  }

  GST_OBJECT_UNLOCK (srtobject->element);
  return TRUE;

err:
  GST_OBJECT_UNLOCK (srtobject->element);
  return FALSE;
}

GstSRTObject *
gst_srt_object_new (GstElement * element)
{
  GstSRTObject *srtobject;

  if (g_atomic_int_add (&srt_init_refcount, 1) == 0) {
    GST_DEBUG_OBJECT (element, "Starting up SRT");
    if (srt_startup () < 0) {
      g_warning ("Failed to initialize SRT (reason: %s)",
          srt_getlasterror_str ());
    }
  }

  srtobject = g_new0 (GstSRTObject, 1);
  srtobject->element = element;
  srtobject->parameters = gst_structure_new_empty ("application/x-srt-params");
  srtobject->sock = SRT_INVALID_SOCK;
  srtobject->poll_id = srt_epoll_create ();
  srtobject->listener_sock = SRT_INVALID_SOCK;
  srtobject->listener_poll_id = SRT_ERROR;
  srtobject->sent_headers = FALSE;
  srtobject->wait_for_connection = GST_SRT_DEFAULT_WAIT_FOR_CONNECTION;

  g_cond_init (&srtobject->sock_cond);
  return srtobject;
}

void
gst_srt_object_destroy (GstSRTObject * srtobject)
{
  g_return_if_fail (srtobject != NULL);

  if (srtobject->poll_id != SRT_ERROR) {
    srt_epoll_release (srtobject->poll_id);
    srtobject->poll_id = SRT_ERROR;
  }

  g_cond_clear (&srtobject->sock_cond);

  GST_DEBUG_OBJECT (srtobject->element, "Destroying srtobject");
  gst_structure_free (srtobject->parameters);

  if (g_atomic_int_dec_and_test (&srt_init_refcount)) {
    srt_cleanup ();
    GST_DEBUG_OBJECT (srtobject->element, "Cleaning up SRT");
  }

  g_clear_pointer (&srtobject->uri, gst_uri_unref);

  g_free (srtobject);
}

gboolean
gst_srt_object_set_property_helper (GstSRTObject * srtobject,
    guint prop_id, const GValue * value, GParamSpec * pspec)
{
  GST_OBJECT_LOCK (srtobject->element);

  switch (prop_id) {
    case PROP_URI:
      gst_srt_object_set_uri (srtobject, g_value_get_string (value), NULL);
      break;
    case PROP_MODE:
      gst_structure_set_value (srtobject->parameters, "mode", value);
      break;
    case PROP_POLL_TIMEOUT:
      gst_structure_set_value (srtobject->parameters, "poll-timeout", value);
      break;
    case PROP_LATENCY:
      gst_structure_set_value (srtobject->parameters, "latency", value);
      break;
    case PROP_LOCALADDRESS:
      gst_structure_set_value (srtobject->parameters, "localaddress", value);
      break;
    case PROP_LOCALPORT:
      gst_structure_set_value (srtobject->parameters, "localport", value);
      break;
    case PROP_PASSPHRASE:
      gst_structure_set_value (srtobject->parameters, "passphrase", value);
      break;
    case PROP_PBKEYLEN:
      gst_structure_set_value (srtobject->parameters, "pbkeylen", value);
      break;
    case PROP_WAIT_FOR_CONNECTION:
      srtobject->wait_for_connection = g_value_get_boolean (value);
      break;
    case PROP_STREAMID:
      gst_structure_set_value (srtobject->parameters, "streamid", value);
      break;
    default:
      goto err;
  }

  GST_OBJECT_UNLOCK (srtobject->element);
  return TRUE;

err:
  GST_OBJECT_UNLOCK (srtobject->element);
  return FALSE;
}

gboolean
gst_srt_object_get_property_helper (GstSRTObject * srtobject,
    guint prop_id, GValue * value, GParamSpec * pspec)
{
  GST_OBJECT_LOCK (srtobject->element);

  switch (prop_id) {
    case PROP_URI:
      g_value_take_string (value, gst_uri_to_string (srtobject->uri));
      break;
    case PROP_MODE:{
      GstSRTConnectionMode v;
      if (!gst_structure_get_enum (srtobject->parameters, "mode",
              GST_TYPE_SRT_CONNECTION_MODE, (gint *) & v)) {
        GST_WARNING_OBJECT (srtobject->element, "Failed to get 'mode'");
        v = GST_SRT_CONNECTION_MODE_NONE;
      }
      g_value_set_enum (value, v);
      break;
    }
    case PROP_LOCALADDRESS:
      g_value_set_string (value,
          gst_structure_get_string (srtobject->parameters, "localaddress"));
      break;
    case PROP_LOCALPORT:{
      guint v;
      if (!gst_structure_get_uint (srtobject->parameters, "localport", &v)) {
        GST_WARNING_OBJECT (srtobject->element, "Failed to get 'localport'");
        v = GST_SRT_DEFAULT_PORT;
      }
      g_value_set_uint (value, v);
      break;
    }
    case PROP_PBKEYLEN:{
      GstSRTKeyLength v;
      if (!gst_structure_get_enum (srtobject->parameters, "pbkeylen",
              GST_TYPE_SRT_KEY_LENGTH, (gint *) & v)) {
        GST_WARNING_OBJECT (srtobject->element, "Failed to get 'pbkeylen'");
        v = GST_SRT_KEY_LENGTH_NO_KEY;
      }
      g_value_set_enum (value, v);
      break;
    }
    case PROP_POLL_TIMEOUT:{
      gint v;
      if (!gst_structure_get_int (srtobject->parameters, "poll-timeout", &v)) {
        GST_WARNING_OBJECT (srtobject->element, "Failed to get 'poll-timeout'");
        v = GST_SRT_DEFAULT_POLL_TIMEOUT;
      }
      g_value_set_int (value, v);
      break;
    }
    case PROP_LATENCY:{
      gint v;
      if (!gst_structure_get_int (srtobject->parameters, "latency", &v)) {
        GST_WARNING_OBJECT (srtobject->element, "Failed to get 'latency'");
        v = GST_SRT_DEFAULT_LATENCY;
      }
      g_value_set_int (value, v);
      break;
    }
    case PROP_STATS:
      g_value_take_boxed (value, gst_srt_object_get_stats (srtobject));
      break;
    case PROP_WAIT_FOR_CONNECTION:
      g_value_set_boolean (value, srtobject->wait_for_connection);
      break;
    case PROP_STREAMID:{
      g_value_set_string (value,
          gst_structure_get_string (srtobject->parameters, "streamid"));
      break;
    }
    default:
      goto err;
  }

  GST_OBJECT_UNLOCK (srtobject->element);
  return TRUE;

err:
  GST_OBJECT_UNLOCK (srtobject->element);
  return FALSE;
}

void
gst_srt_object_install_properties_helper (GObjectClass * gobject_class)
{
  /**
   * GstSRTSrc:uri:
   *
   * The URI used by SRT connection. User can specify SRT specific options by URI parameters.
   * Refer to <a href="https://github.com/Haivision/srt/blob/master/docs/stransmit.md#medium-srt">Mediun: SRT</a>
   */
  g_object_class_install_property (gobject_class, PROP_URI,
      g_param_spec_string ("uri", "URI",
          "URI in the form of srt://address:port", GST_SRT_DEFAULT_URI,
          G_PARAM_READWRITE | GST_PARAM_MUTABLE_READY |
          G_PARAM_STATIC_STRINGS));

  /**
   * GstSRTSrc:mode:
   *
   * The SRT connection mode.
   * This property can be set by URI parameters.
   */
  g_object_class_install_property (gobject_class, PROP_MODE,
      g_param_spec_enum ("mode", "Connection mode",
          "SRT connection mode", GST_TYPE_SRT_CONNECTION_MODE,
          GST_SRT_CONNECTION_MODE_CALLER,
          G_PARAM_READWRITE | GST_PARAM_MUTABLE_READY |
          G_PARAM_STATIC_STRINGS));
  gst_type_mark_as_plugin_api (GST_TYPE_SRT_CONNECTION_MODE, 0);

  /**
   * GstSRTSrc:localaddress:
   *
   * The address to bind when #GstSRTSrc:mode is listener or rendezvous.
   * This property can be set by URI parameters.
   */
  g_object_class_install_property (gobject_class, PROP_LOCALADDRESS,
      g_param_spec_string ("localaddress", "Local address",
          "Local address to bind", GST_SRT_DEFAULT_LOCALADDRESS,
          G_PARAM_READWRITE | GST_PARAM_MUTABLE_READY |
          G_PARAM_STATIC_STRINGS));

  /**
   * GstSRTSrc:localport:
   *
   * The local port to bind when #GstSRTSrc:mode is listener or rendezvous.
   * This property can be set by URI parameters.
   */
  g_object_class_install_property (gobject_class, PROP_LOCALPORT,
      g_param_spec_uint ("localport", "Local port",
          "Local port to bind", 0,
          65535, GST_SRT_DEFAULT_PORT,
          G_PARAM_READWRITE | GST_PARAM_MUTABLE_READY |
          G_PARAM_STATIC_STRINGS));

  /**
   * GstSRTSrc:passphrase:
   *
   * The password for the encrypted transmission.
   * This property can be set by URI parameters.
   */
  g_object_class_install_property (gobject_class, PROP_PASSPHRASE,
      g_param_spec_string ("passphrase", "Passphrase",
          "Password for the encrypted transmission", "",
          G_PARAM_WRITABLE | GST_PARAM_MUTABLE_READY | G_PARAM_STATIC_STRINGS));

  /**
   * GstSRTSrc:pbkeylen:
   *
   * The crypto key length.
   * This property can be set by URI parameters.
   */
  g_object_class_install_property (gobject_class, PROP_PBKEYLEN,
      g_param_spec_enum ("pbkeylen", "Crypto key length",
          "Crypto key length in bytes", GST_TYPE_SRT_KEY_LENGTH,
          GST_SRT_DEFAULT_PBKEYLEN,
          G_PARAM_READWRITE | GST_PARAM_MUTABLE_READY |
          G_PARAM_STATIC_STRINGS));
  gst_type_mark_as_plugin_api (GST_TYPE_SRT_KEY_LENGTH, 0);

  /**
   * GstSRTSrc:poll-timeout:
   *
   * The polling timeout used when srt poll is started.
   * Even if the default value indicates infinite waiting, it can be cancellable according to #GstState
   * This property can be set by URI parameters.
   */
  g_object_class_install_property (gobject_class, PROP_POLL_TIMEOUT,
      g_param_spec_int ("poll-timeout", "Poll timeout",
          "Return poll wait after timeout milliseconds (-1 = infinite)", -1,
          G_MAXINT32, GST_SRT_DEFAULT_POLL_TIMEOUT,
          G_PARAM_READWRITE | GST_PARAM_MUTABLE_READY |
          G_PARAM_STATIC_STRINGS));

  /**
   * GstSRTSrc:latency:
   *
   * The maximum accepted transmission latency.
   */
  g_object_class_install_property (gobject_class, PROP_LATENCY,
      g_param_spec_int ("latency", "latency",
          "Minimum latency (milliseconds)", 0,
          G_MAXINT32, GST_SRT_DEFAULT_LATENCY,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  /**
   * GstSRTSrc:stats:
   *
   * The statistics from SRT.
   */
  g_object_class_install_property (gobject_class, PROP_STATS,
      g_param_spec_boxed ("stats", "Statistics",
          "SRT Statistics", GST_TYPE_STRUCTURE,
          G_PARAM_READABLE | G_PARAM_STATIC_STRINGS));

  /**
   * GstSRTSink:wait-for-connection:
   *
   * Boolean to block streaming until a client connects.  If TRUE,
   * `srtsink' will stream only when a client is connected.
   */
  g_object_class_install_property (gobject_class, PROP_WAIT_FOR_CONNECTION,
      g_param_spec_boolean ("wait-for-connection",
          "Wait for a connection",
          "Block the stream until a client connects",
          GST_SRT_DEFAULT_WAIT_FOR_CONNECTION,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  /**
   * GstSRTSrc:streamid:
   *
   * The stream id for the SRT access control.
   */
  g_object_class_install_property (gobject_class, PROP_STREAMID,
      g_param_spec_string ("streamid", "Stream ID",
          "Stream ID for the SRT access control", "",
          G_PARAM_READWRITE | GST_PARAM_MUTABLE_READY |
          G_PARAM_STATIC_STRINGS));
}

static void
gst_srt_object_set_enum_value (GstStructure * s, GType enum_type,
    gconstpointer key, gconstpointer value)
{
  GEnumClass *enum_class;
  GEnumValue *enum_value;

  enum_class = g_type_class_ref (enum_type);
  enum_value = g_enum_get_value_by_nick (enum_class, value);

  if (enum_value) {
    gst_structure_set (s, key, enum_type, enum_value->value, NULL);
  }

  g_type_class_unref (enum_class);
}

static void
gst_srt_object_set_string_value (GstStructure * s, const gchar * key,
    const gchar * value)
{
  gst_structure_set (s, key, G_TYPE_STRING, value, NULL);
}

static void
gst_srt_object_set_uint_value (GstStructure * s, const gchar * key,
    const gchar * value)
{
  gst_structure_set (s, key, G_TYPE_UINT,
      (guint) g_ascii_strtoll (value, NULL, 10), NULL);
}

static void
gst_srt_object_set_int_value (GstStructure * s, const gchar * key,
    const gchar * value)
{
  gst_structure_set (s, key, G_TYPE_INT,
      (gint) g_ascii_strtoll (value, NULL, 10), NULL);
}

static void
gst_srt_object_validate_parameters (GstStructure * s, GstUri * uri)
{
  GstSRTConnectionMode connection_mode = GST_SRT_CONNECTION_MODE_NONE;

  gst_structure_get_enum (s, "mode", GST_TYPE_SRT_CONNECTION_MODE,
      (gint *) & connection_mode);

  if (connection_mode == GST_SRT_CONNECTION_MODE_RENDEZVOUS ||
      connection_mode == GST_SRT_CONNECTION_MODE_LISTENER) {
    guint local_port;
    const gchar *local_address = gst_structure_get_string (s, "localaddress");

    if (local_address == NULL) {
      local_address =
          gst_uri_get_host (uri) ==
          NULL ? GST_SRT_DEFAULT_LOCALADDRESS : gst_uri_get_host (uri);
      gst_srt_object_set_string_value (s, "localaddress", local_address);
    }

    if (!gst_structure_get_uint (s, "localport", &local_port)) {
      local_port =
          gst_uri_get_port (uri) ==
          GST_URI_NO_PORT ? GST_SRT_DEFAULT_PORT : gst_uri_get_port (uri);
      gst_structure_set (s, "localport", G_TYPE_UINT, local_port, NULL);
    }
  }
}

/* called with GST_OBJECT_LOCK (srtobject->element) held */
gboolean
gst_srt_object_set_uri (GstSRTObject * srtobject, const gchar * uri,
    GError ** err)
{
  GHashTable *query_table = NULL;
  GHashTableIter iter;
  gpointer key, value;
  const char *addr_str;

  if (srtobject->opened) {
    g_warning
        ("It's not supported to change the 'uri' property when SRT socket is opened.");
    g_set_error (err, GST_URI_ERROR, GST_URI_ERROR_BAD_STATE,
        "It's not supported to change the 'uri' property when SRT socket is opened");

    return FALSE;
  }

  if (!g_str_has_prefix (uri, GST_SRT_DEFAULT_URI_SCHEME)) {
    g_warning ("Given uri cannot be used for SRT connection.");
    g_set_error (err, GST_URI_ERROR, GST_URI_ERROR_BAD_URI,
        "Invalid SRT URI scheme");
    return FALSE;
  }

  g_clear_pointer (&srtobject->uri, gst_uri_unref);
  srtobject->uri = gst_uri_from_string (uri);

  g_clear_pointer (&srtobject->parameters, gst_structure_free);
  srtobject->parameters = gst_structure_new ("application/x-srt-params",
      "poll-timeout", G_TYPE_INT, GST_SRT_DEFAULT_POLL_TIMEOUT,
      "latency", G_TYPE_INT, GST_SRT_DEFAULT_LATENCY, NULL);

  query_table = gst_uri_get_query_table (srtobject->uri);

  GST_DEBUG_OBJECT (srtobject->element,
      "set uri to (host: %s, port: %d) with %d query strings",
      gst_uri_get_host (srtobject->uri), gst_uri_get_port (srtobject->uri),
      query_table == NULL ? 0 : g_hash_table_size (query_table));

  addr_str = gst_uri_get_host (srtobject->uri);
  if (addr_str)
    gst_srt_object_set_enum_value (srtobject->parameters,
        GST_TYPE_SRT_CONNECTION_MODE, "mode", "caller");
  else
    gst_srt_object_set_enum_value (srtobject->parameters,
        GST_TYPE_SRT_CONNECTION_MODE, "mode", "listener");

  if (query_table) {
    g_hash_table_iter_init (&iter, query_table);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
      if (!g_strcmp0 ("mode", key)) {
        gst_srt_object_set_enum_value (srtobject->parameters,
            GST_TYPE_SRT_CONNECTION_MODE, key, value);
      } else if (!g_strcmp0 ("localaddress", key)) {
        gst_srt_object_set_string_value (srtobject->parameters, key, value);
      } else if (!g_strcmp0 ("localport", key)) {
        gst_srt_object_set_uint_value (srtobject->parameters, key, value);
      } else if (!g_strcmp0 ("passphrase", key)) {
        gst_srt_object_set_string_value (srtobject->parameters, key, value);
      } else if (!g_strcmp0 ("pbkeylen", key)) {
        gst_srt_object_set_enum_value (srtobject->parameters,
            GST_TYPE_SRT_KEY_LENGTH, key, value);
      } else if (!g_strcmp0 ("streamid", key)) {
        gst_srt_object_set_string_value (srtobject->parameters, key, value);
      } else if (!g_strcmp0 ("latency", key)) {
        gst_srt_object_set_int_value (srtobject->parameters, key, value);
      } else if (!g_strcmp0 ("poll-timeout", key)) {
        gst_srt_object_set_int_value (srtobject->parameters, key, value);
      }
    }

    g_hash_table_unref (query_table);
  }

  gst_srt_object_validate_parameters (srtobject->parameters, srtobject->uri);

  return TRUE;
}

static gpointer
thread_func (gpointer data)
{
  GstSRTObject *srtobject = data;
  SRTSOCKET caller_sock;
  union
  {
    struct sockaddr_storage ss;
    struct sockaddr sa;
  } caller_sa;
  int caller_sa_len = sizeof (caller_sa);

  gint poll_timeout;

  SRTSOCKET rsock;
  gint rsocklen = 1;

  for (;;) {
    GST_OBJECT_LOCK (srtobject->element);
    if (!gst_structure_get_int (srtobject->parameters, "poll-timeout",
            &poll_timeout)) {
      poll_timeout = GST_SRT_DEFAULT_POLL_TIMEOUT;
    }
    GST_OBJECT_UNLOCK (srtobject->element);

    GST_DEBUG_OBJECT (srtobject->element, "Waiting a request from caller");

    if (srt_epoll_wait (srtobject->listener_poll_id, &rsock,
            &rsocklen, 0, 0, poll_timeout, NULL, 0, NULL, 0) < 0) {
      gint srt_errno = srt_getlasterror (NULL);

      if (srtobject->listener_poll_id == SRT_ERROR)
        return NULL;
      if (srt_errno == SRT_ETIMEOUT) {
        continue;
      } else {
        GST_ELEMENT_ERROR (srtobject->element, RESOURCE, FAILED,
            ("abort polling: %s", srt_getlasterror_str ()), (NULL));
        return NULL;
      }
    }

    caller_sock =
        srt_accept (srtobject->listener_sock, &caller_sa.sa, &caller_sa_len);

    if (caller_sock != SRT_INVALID_SOCK) {
      SRTCaller *caller;
      gint flag = SRT_EPOLL_ERR;

      caller = srt_caller_new ();
      caller->sockaddr =
          g_socket_address_new_from_native (&caller_sa.sa, caller_sa_len);
      caller->poll_id = srt_epoll_create ();
      caller->sock = caller_sock;

      if (gst_uri_handler_get_uri_type (GST_URI_HANDLER
              (srtobject->element)) == GST_URI_SRC) {
        flag |= SRT_EPOLL_IN;
      } else {
        flag |= SRT_EPOLL_OUT;
      }

      if (srt_epoll_add_usock (caller->poll_id, caller_sock, &flag)) {

        GST_ELEMENT_ERROR (srtobject->element, RESOURCE, SETTINGS,
            ("%s", srt_getlasterror_str ()), (NULL));

        srt_caller_free (caller);

        /* try-again */
        continue;
      }

      GST_DEBUG_OBJECT (srtobject->element, "Accept to connect %d",
          caller->sock);

      g_mutex_lock (&srtobject->sock_lock);
      srtobject->callers = g_list_append (srtobject->callers, caller);
      g_cond_signal (&srtobject->sock_cond);
      g_mutex_unlock (&srtobject->sock_lock);

      /* notifying caller-added */
      g_signal_emit_by_name (srtobject->element, "caller-added", caller->sock,
          caller->sockaddr);

      if (gst_uri_handler_get_uri_type (GST_URI_HANDLER (srtobject->element)) ==
          GST_URI_SRC)
        return NULL;
    }
  }
}

static gboolean
gst_srt_object_wait_connect (GstSRTObject * srtobject,
    GCancellable * cancellable, gpointer sa, size_t sa_len, GError ** error)
{
  SRTSOCKET sock = SRT_INVALID_SOCK;
  const gchar *local_address = NULL;
  guint local_port = 0;
  gint sock_flags = SRT_EPOLL_ERR | SRT_EPOLL_IN;

  gpointer bind_sa;
  gsize bind_sa_len;
  GSocketAddress *bind_addr = NULL;

  GST_OBJECT_LOCK (srtobject->element);

  gst_structure_get_uint (srtobject->parameters, "localport", &local_port);

  local_address =
      gst_structure_get_string (srtobject->parameters, "localaddress");
  if (local_address == NULL)
    local_address = GST_SRT_DEFAULT_LOCALADDRESS;

  GST_OBJECT_UNLOCK (srtobject->element);

  bind_addr =
      gst_srt_object_resolve (srtobject, local_address, local_port, cancellable,
      error);
  if (!bind_addr) {
    goto failed;
  }

  bind_sa_len = g_socket_address_get_native_size (bind_addr);
  bind_sa = g_alloca (bind_sa_len);

  if (!g_socket_address_to_native (bind_addr, bind_sa, bind_sa_len, error)) {
    goto failed;
  }

  g_clear_object (&bind_addr);

  sock = srt_create_socket ();
  if (sock == SRT_INVALID_SOCK) {
    g_set_error (error, GST_LIBRARY_ERROR, GST_LIBRARY_ERROR_INIT, "%s",
        srt_getlasterror_str ());
    goto failed;
  }

  if (!gst_srt_object_set_common_params (sock, srtobject, error)) {
    goto failed;
  }

  GST_DEBUG_OBJECT (srtobject->element, "Binding to %s (port: %d)",
      local_address, local_port);

  if (srt_bind (sock, bind_sa, bind_sa_len) == SRT_ERROR) {
    g_set_error (error, GST_RESOURCE_ERROR,
        GST_RESOURCE_ERROR_OPEN_READ_WRITE, "Cannot bind to %s:%d - %s",
        local_address, local_port, srt_getlasterror_str ());
    goto failed;
  }

  if (srt_epoll_add_usock (srtobject->listener_poll_id, sock, &sock_flags)) {
    g_set_error (error, GST_LIBRARY_ERROR, GST_LIBRARY_ERROR_SETTINGS, "%s",
        srt_getlasterror_str ());
    goto failed;
  }

  GST_DEBUG_OBJECT (srtobject->element, "Starting to listen on bind socket");
  if (srt_listen (sock, 1) == SRT_ERROR) {
    g_set_error (error, GST_RESOURCE_ERROR,
        GST_RESOURCE_ERROR_OPEN_READ_WRITE, "Cannot listen on bind socket: %s",
        srt_getlasterror_str ());

    goto failed;
  }

  srtobject->listener_sock = sock;

  srtobject->thread =
      g_thread_try_new ("GstSRTObjectListener", thread_func, srtobject, error);

  if (*error != NULL) {
    goto failed;
  }

  return TRUE;

failed:

  if (srtobject->listener_poll_id != SRT_ERROR) {
    srt_epoll_release (srtobject->listener_poll_id);
  }

  if (sock != SRT_INVALID_SOCK) {
    srt_close (sock);
  }

  g_clear_object (&bind_addr);

  srtobject->listener_poll_id = SRT_ERROR;
  srtobject->listener_sock = SRT_INVALID_SOCK;

  return FALSE;
}

static gboolean
gst_srt_object_connect (GstSRTObject * srtobject, GCancellable * cancellable,
    GstSRTConnectionMode connection_mode, gpointer sa, size_t sa_len,
    GError ** error)
{
  SRTSOCKET sock;
  gint sock_flags = SRT_EPOLL_ERR;
  guint local_port = 0;
  const gchar *local_address = NULL;
  bool sender;
  bool rendezvous;

  sock = srt_create_socket ();
  if (sock == SRT_INVALID_SOCK) {
    g_set_error (error, GST_LIBRARY_ERROR, GST_LIBRARY_ERROR_INIT, "%s",
        srt_getlasterror_str ());
    goto failed;
  }

  if (!gst_srt_object_set_common_params (sock, srtobject, error)) {
    goto failed;
  }

  switch (gst_uri_handler_get_uri_type (GST_URI_HANDLER (srtobject->element))) {
    case GST_URI_SRC:
      sender = false;
      sock_flags |= SRT_EPOLL_IN;
      break;
    case GST_URI_SINK:
      sender = true;
      sock_flags |= SRT_EPOLL_OUT;
      break;
    default:
      g_set_error (error, GST_LIBRARY_ERROR, GST_LIBRARY_ERROR_SETTINGS,
          "Cannot determine stream direction");
      goto failed;
  }

  if (srt_setsockopt (sock, 0, SRTO_SENDER, &sender, sizeof sender)) {
    g_set_error (error, GST_LIBRARY_ERROR, GST_LIBRARY_ERROR_SETTINGS, "%s",
        srt_getlasterror_str ());
    goto failed;
  }

  rendezvous = (connection_mode == GST_SRT_CONNECTION_MODE_RENDEZVOUS);
  if (srt_setsockopt (sock, 0, SRTO_RENDEZVOUS, &rendezvous, sizeof rendezvous)) {
    g_set_error (error, GST_LIBRARY_ERROR, GST_LIBRARY_ERROR_SETTINGS, "%s",
        srt_getlasterror_str ());
    goto failed;
  }

  GST_OBJECT_LOCK (srtobject->element);
  gst_structure_get_uint (srtobject->parameters, "localport", &local_port);
  local_address =
      gst_structure_get_string (srtobject->parameters, "localaddress");
  GST_OBJECT_UNLOCK (srtobject->element);

  /* According to SRT norm, bind local address and port if specified */
  if (local_address != NULL && local_port != 0) {
    gpointer bind_sa;
    gsize bind_sa_len;

    GSocketAddress *bind_addr =
        gst_srt_object_resolve (srtobject, local_address,
        local_port, cancellable, error);

    if (!bind_addr) {
      goto failed;
    }

    bind_sa_len = g_socket_address_get_native_size (bind_addr);
    bind_sa = g_alloca (bind_sa_len);

    if (!g_socket_address_to_native (bind_addr, bind_sa, bind_sa_len, error)) {
      g_clear_object (&bind_addr);
      goto failed;
    }

    g_clear_object (&bind_addr);

    GST_DEBUG_OBJECT (srtobject->element, "Binding to %s (port: %d)",
        local_address, local_port);

    if (srt_bind (sock, bind_sa, bind_sa_len) == SRT_ERROR) {
      g_set_error (error, GST_RESOURCE_ERROR,
          GST_RESOURCE_ERROR_OPEN_READ_WRITE, "Cannot bind to %s:%d - %s",
          local_address, local_port, srt_getlasterror_str ());
      goto failed;
    }
  }

  if (srt_epoll_add_usock (srtobject->poll_id, sock, &sock_flags)) {
    g_set_error (error, GST_LIBRARY_ERROR, GST_LIBRARY_ERROR_SETTINGS, "%s",
        srt_getlasterror_str ());
    goto failed;
  }

  if (srt_connect (sock, sa, sa_len) == SRT_ERROR) {
    g_set_error (error, GST_RESOURCE_ERROR, GST_RESOURCE_ERROR_OPEN_READ, "%s",
        srt_getlasterror_str ());
    goto failed;
  }

  srtobject->sock = sock;

  return TRUE;

failed:

  if (srtobject->poll_id != SRT_ERROR) {
    srt_epoll_release (srtobject->poll_id);
  }

  if (sock != SRT_INVALID_SOCK) {
    srt_close (sock);
  }

  srtobject->poll_id = SRT_ERROR;
  srtobject->sock = SRT_INVALID_SOCK;

  return FALSE;
}

static gboolean
gst_srt_object_open_connection (GstSRTObject * srtobject,
    GCancellable * cancellable, GstSRTConnectionMode connection_mode,
    gpointer sa, size_t sa_len, GError ** error)
{
  gboolean ret = FALSE;

  if (connection_mode == GST_SRT_CONNECTION_MODE_LISTENER) {
    ret =
        gst_srt_object_wait_connect (srtobject, cancellable, sa, sa_len, error);
  } else {
    ret =
        gst_srt_object_connect (srtobject, cancellable, connection_mode, sa,
        sa_len, error);
  }

  return ret;
}

static gboolean
gst_srt_object_open_internal (GstSRTObject * srtobject,
    GCancellable * cancellable, GError ** error)
{
  GSocketAddress *socket_address = NULL;
  GstSRTConnectionMode connection_mode;

  gpointer sa;
  size_t sa_len;
  const gchar *addr_str;
  guint port;
  gboolean ret = FALSE;

  GST_OBJECT_LOCK (srtobject->element);

  srtobject->opened = FALSE;

  if (!gst_structure_get_enum (srtobject->parameters,
          "mode", GST_TYPE_SRT_CONNECTION_MODE, (gint *) & connection_mode)) {
    GST_WARNING_OBJECT (srtobject->element,
        "Cannot get connection mode information." " Use default mode");
    connection_mode = GST_SRT_DEFAULT_MODE;
  }

  addr_str = gst_uri_get_host (srtobject->uri);
  if (addr_str == NULL) {
    connection_mode = GST_SRT_CONNECTION_MODE_LISTENER;
    addr_str = GST_SRT_DEFAULT_LOCALADDRESS;
    GST_DEBUG_OBJECT (srtobject->element,
        "Given uri doesn't have hostname or address. Use any (%s) and"
        " setting listener mode", addr_str);
  }

  port = gst_uri_get_port (srtobject->uri);

  GST_DEBUG_OBJECT (srtobject->element,
      "Opening SRT socket with parameters: %" GST_PTR_FORMAT,
      srtobject->parameters);

  GST_OBJECT_UNLOCK (srtobject->element);

  socket_address =
      gst_srt_object_resolve (srtobject, addr_str, port, cancellable, error);
  if (socket_address == NULL) {
    goto out;
  }

  sa_len = g_socket_address_get_native_size (socket_address);
  sa = g_alloca (sa_len);

  if (!g_socket_address_to_native (socket_address, sa, sa_len, error)) {
    goto out;
  }

  srtobject->listener_poll_id = srt_epoll_create ();

  ret =
      gst_srt_object_open_connection
      (srtobject, cancellable, connection_mode, sa, sa_len, error);

  GST_OBJECT_LOCK (srtobject->element);
  srtobject->opened = ret;
  GST_OBJECT_UNLOCK (srtobject->element);

out:
  g_clear_object (&socket_address);

  return ret;
}

gboolean
gst_srt_object_open (GstSRTObject * srtobject, GCancellable * cancellable,
    GError ** error)
{
  srtobject->previous_bytes = 0;

  return gst_srt_object_open_internal (srtobject, cancellable, error);
}

void
gst_srt_object_close (GstSRTObject * srtobject)
{
  g_mutex_lock (&srtobject->sock_lock);

  if (srtobject->sock != SRT_INVALID_SOCK) {
    GstStructure *stats;

    if (srtobject->poll_id != SRT_ERROR) {
      srt_epoll_remove_usock (srtobject->poll_id, srtobject->sock);
    }

    stats = gst_srt_object_accumulate_stats (srtobject, srtobject->sock);

    /* FIXME: These are the final statistics for the socket before we close it.
     * Deliver the stats to the app before we throw them away. */
    gst_structure_free (stats);

    GST_DEBUG_OBJECT (srtobject->element, "Closing SRT socket (0x%x)",
        srtobject->sock);

    srt_close (srtobject->sock);
    srtobject->sock = SRT_INVALID_SOCK;
  }

  if (srtobject->listener_poll_id != SRT_ERROR) {
    if (srtobject->listener_sock != SRT_INVALID_SOCK) {
      srt_epoll_remove_usock (srtobject->listener_poll_id,
          srtobject->listener_sock);
    }
    srt_epoll_release (srtobject->listener_poll_id);
    srtobject->listener_poll_id = SRT_ERROR;
  }

  if (srtobject->thread) {
    GThread *thread = g_steal_pointer (&srtobject->thread);
    g_mutex_unlock (&srtobject->sock_lock);
    g_thread_join (thread);
    g_mutex_lock (&srtobject->sock_lock);
  }

  if (srtobject->listener_sock != SRT_INVALID_SOCK) {
    GST_DEBUG_OBJECT (srtobject->element, "Closing SRT listener socket (0x%x)",
        srtobject->listener_sock);

    srt_close (srtobject->listener_sock);
    srtobject->listener_sock = SRT_INVALID_SOCK;
  }

  if (srtobject->callers) {
    GList *callers = g_steal_pointer (&srtobject->callers);
    g_list_foreach (callers, (GFunc) srt_caller_signal_removed, srtobject);
    g_list_free_full (callers, (GDestroyNotify) srt_caller_free);
  }

  g_mutex_unlock (&srtobject->sock_lock);

  GST_OBJECT_LOCK (srtobject->element);
  srtobject->opened = FALSE;
  GST_OBJECT_UNLOCK (srtobject->element);
}

static gboolean
gst_srt_object_wait_caller (GstSRTObject * srtobject,
    GCancellable * cancellable, GError ** error)
{
  gboolean ret;

  g_mutex_lock (&srtobject->sock_lock);

  if (srtobject->callers == NULL) {
    GST_INFO_OBJECT (srtobject->element, "Waiting for connection");

    while (!g_cancellable_is_cancelled (cancellable)) {
      ret = (srtobject->callers != NULL);
      if (ret) {
        GST_DEBUG_OBJECT (srtobject->element, "Got a connection");
        break;
      }

      g_cond_wait (&srtobject->sock_cond, &srtobject->sock_lock);
    }
  } else {
    ret = TRUE;
  }

  g_mutex_unlock (&srtobject->sock_lock);

  if (!ret) {
    g_set_error (error, GST_RESOURCE_ERROR, GST_RESOURCE_ERROR_FAILED,
        "Canceled waiting for a connection.");
  }

  return ret;
}

gssize
gst_srt_object_read (GstSRTObject * srtobject,
    guint8 * data, gsize size, GCancellable * cancellable, GError ** error,
    SRT_MSGCTRL * mctrl)
{
  gssize len = 0;
  gint poll_timeout;
  GstSRTConnectionMode connection_mode = GST_SRT_CONNECTION_MODE_NONE;
  gint poll_id = SRT_ERROR;

  /* Only source element can read data */
  g_return_val_if_fail (gst_uri_handler_get_uri_type (GST_URI_HANDLER
          (srtobject->element)) == GST_URI_SRC, -1);

  GST_OBJECT_LOCK (srtobject->element);

  gst_structure_get_enum (srtobject->parameters, "mode",
      GST_TYPE_SRT_CONNECTION_MODE, (gint *) & connection_mode);

  if (!gst_structure_get_int (srtobject->parameters, "poll-timeout",
          &poll_timeout)) {
    poll_timeout = GST_SRT_DEFAULT_POLL_TIMEOUT;
  }

  GST_OBJECT_UNLOCK (srtobject->element);

  if (connection_mode == GST_SRT_CONNECTION_MODE_LISTENER) {
    if (!gst_srt_object_wait_caller (srtobject, cancellable, error))
      return -1;

    g_mutex_lock (&srtobject->sock_lock);
    if (srtobject->callers) {
      SRTCaller *caller = srtobject->callers->data;
      poll_id = caller->poll_id;
    }
    g_mutex_unlock (&srtobject->sock_lock);

    if (poll_id == SRT_ERROR)
      return 0;
  } else {
    poll_id = srtobject->poll_id;
  }

  while (!g_cancellable_is_cancelled (cancellable)) {

    SRTSOCKET rsock;
    gint rsocklen = 1;
    int pollret;

    pollret = srt_epoll_wait (poll_id, &rsock,
        &rsocklen, 0, 0, poll_timeout, NULL, 0, NULL, 0);
    if (pollret < 0) {
      gint srt_errno = srt_getlasterror (NULL);

      if (srt_errno != SRT_ETIMEOUT) {
        return 0;
      }
      continue;
    }

    if (rsocklen < 0) {
      GST_WARNING_OBJECT (srtobject->element,
          "abnormal SRT socket is detected");
      srt_close (rsock);
    }

    switch (srt_getsockstate (rsock)) {
      case SRTS_BROKEN:
      case SRTS_NONEXIST:
      case SRTS_CLOSED:
        if (connection_mode == GST_SRT_CONNECTION_MODE_LISTENER) {
          /* Caller has been disappeared. */
          return 0;
        } else {
          GST_WARNING_OBJECT (srtobject->element,
              "Invalid SRT socket. Trying to reconnect");
          gst_srt_object_close (srtobject);
          if (!gst_srt_object_open_internal (srtobject, cancellable, error)) {
            return -1;
          }
          continue;
        }
      case SRTS_CONNECTED:
        /* good to go */
        break;
      default:
        /* not-ready */
        continue;
    }


    srt_msgctrl_init (mctrl);
    len = srt_recvmsg2 (rsock, (char *) (data), size, mctrl);

    if (len == SRT_ERROR) {
      gint srt_errno = srt_getlasterror (NULL);
      if (srt_errno == SRT_EASYNCRCV) {
        continue;
      } else {
        g_set_error (error, GST_RESOURCE_ERROR, GST_RESOURCE_ERROR_READ,
            "Failed to receive from SRT socket: %s", srt_getlasterror_str ());
        return -1;
      }
    }
    break;
  }

  return len;
}

void
gst_srt_object_wakeup (GstSRTObject * srtobject, GCancellable * cancellable)
{
  GST_DEBUG_OBJECT (srtobject->element, "waking up SRT");

  /* Removing all socket descriptors from the monitoring list
   * wakes up SRT's threads. We only have one to remove. */
  if (srtobject->sock != SRT_INVALID_SOCK && srtobject->poll_id != SRT_ERROR) {
    srt_epoll_remove_usock (srtobject->poll_id, srtobject->sock);
  }

  /* connection is only waited for in listener mode,
   * but there is no harm in raising signal in any case */
  g_mutex_lock (&srtobject->sock_lock);
  /* however, a race might be harmful ...
   * the cancellation is used as 'flushing' flag here,
   * so make sure it is so detected by the intended part at proper time */
  g_cancellable_cancel (cancellable);
  g_cond_signal (&srtobject->sock_cond);
  g_mutex_unlock (&srtobject->sock_lock);
}

static gboolean
gst_srt_object_send_headers (GstSRTObject * srtobject, SRTSOCKET sock,
    gint poll_id, gint poll_timeout, GstBufferList * headers,
    GCancellable * cancellable)
{
  guint size, i;

  if (!headers)
    return TRUE;

  size = gst_buffer_list_length (headers);

  GST_DEBUG_OBJECT (srtobject->element, "Sending %u stream headers", size);

  for (i = 0; i < size; i++) {
    SRTSOCKET wsock = sock;
    gint wsocklen = 1;

    GstBuffer *buffer = gst_buffer_list_get (headers, i);
    GstMapInfo mapinfo;

    if (g_cancellable_is_cancelled (cancellable)) {
      return FALSE;
    }

    if (poll_id > 0 && srt_epoll_wait (poll_id, 0, 0, &wsock,
            &wsocklen, poll_timeout, NULL, 0, NULL, 0) < 0) {
      continue;
    }

    GST_TRACE_OBJECT (srtobject->element, "sending header %u %" GST_PTR_FORMAT,
        i, buffer);

    if (!gst_buffer_map (buffer, &mapinfo, GST_MAP_READ)) {
      GST_ELEMENT_ERROR (srtobject->element, RESOURCE, READ,
          ("Could not map the input stream"), (NULL));
      return FALSE;
    }

    if (srt_sendmsg2 (wsock, (char *) mapinfo.data, mapinfo.size,
            0) == SRT_ERROR) {
      GST_ELEMENT_ERROR (srtobject->element, RESOURCE, WRITE, NULL,
          ("%s", srt_getlasterror_str ()));
      gst_buffer_unmap (buffer, &mapinfo);
      return FALSE;
    }

    gst_buffer_unmap (buffer, &mapinfo);
  }

  return TRUE;
}

static gssize
gst_srt_object_write_to_callers (GstSRTObject * srtobject,
    GstBufferList * headers,
    const GstMapInfo * mapinfo, GCancellable * cancellable, GError ** error)
{
  GList *callers;

  g_mutex_lock (&srtobject->sock_lock);
  callers = srtobject->callers;
  while (callers != NULL) {
    gssize len = 0;
    const guint8 *msg = mapinfo->data;
    gint sent;
    gint payload_size, optlen = 1;

    SRTCaller *caller = callers->data;
    callers = callers->next;

    if (g_cancellable_is_cancelled (cancellable)) {
      goto cancelled;
    }

    if (!caller->sent_headers) {
      if (!gst_srt_object_send_headers (srtobject, caller->sock, -1,
              -1, headers, cancellable)) {
        goto err;
      }
      caller->sent_headers = TRUE;
    }

    if (srt_getsockflag (caller->sock, SRTO_PAYLOADSIZE, &payload_size,
            &optlen)) {
      GST_WARNING_OBJECT (srtobject->element, "%s", srt_getlasterror_str ());
      goto err;
    }

    while (len < mapinfo->size) {
      gint rest = MIN (mapinfo->size - len, payload_size);
      sent = srt_sendmsg2 (caller->sock, (char *) (msg + len), rest, 0);
      if (sent < 0) {
        GST_WARNING_OBJECT (srtobject->element, "Dropping caller %d: %s",
            caller->sock, srt_getlasterror_str ());
        goto err;
      }
      len += sent;
    }

    continue;

  err:
    srtobject->callers = g_list_remove (srtobject->callers, caller);
    srt_caller_signal_removed (caller, srtobject);
    srt_caller_free (caller);
  }

  g_mutex_unlock (&srtobject->sock_lock);
  return mapinfo->size;

cancelled:
  g_mutex_unlock (&srtobject->sock_lock);
  return -1;
}

static gssize
gst_srt_object_write_one (GstSRTObject * srtobject,
    GstBufferList * headers,
    const GstMapInfo * mapinfo, GCancellable * cancellable, GError ** error)
{
  gssize len = 0;
  gint poll_timeout;
  const guint8 *msg = mapinfo->data;
  gint payload_size, optlen = 1;

  GST_OBJECT_LOCK (srtobject->element);
  if (!gst_structure_get_int (srtobject->parameters, "poll-timeout",
          &poll_timeout)) {
    poll_timeout = GST_SRT_DEFAULT_POLL_TIMEOUT;
  }
  GST_OBJECT_UNLOCK (srtobject->element);

  if (!srtobject->sent_headers) {
    if (!gst_srt_object_send_headers (srtobject, srtobject->sock,
            srtobject->poll_id, poll_timeout, headers, cancellable)) {
      return -1;
    }
    srtobject->sent_headers = TRUE;
  }

  while (len < mapinfo->size) {
    SRTSOCKET wsock;
    gint wsocklen = 1;

    gint sent;
    gint rest;

    if (g_cancellable_is_cancelled (cancellable)) {
      break;
    }

    if (srt_epoll_wait (srtobject->poll_id, 0, 0, &wsock,
            &wsocklen, poll_timeout, NULL, 0, NULL, 0) < 0) {
      continue;
    }

    switch (srt_getsockstate (wsock)) {
      case SRTS_BROKEN:
      case SRTS_NONEXIST:
      case SRTS_CLOSED:
        GST_WARNING_OBJECT (srtobject->element,
            "Invalid SRT socket. Trying to reconnect");
        gst_srt_object_close (srtobject);
        if (!gst_srt_object_open_internal (srtobject, cancellable, error)) {
          return -1;
        }
        continue;
      case SRTS_CONNECTED:
        /* good to go */
        GST_LOG_OBJECT (srtobject->element, "good to go");
        break;
      default:
        GST_WARNING_OBJECT (srtobject->element, "not ready");
        /* not-ready */
        continue;
    }

    if (srt_getsockflag (wsock, SRTO_PAYLOADSIZE, &payload_size, &optlen)) {
      GST_ELEMENT_ERROR (srtobject->element, RESOURCE, WRITE, NULL,
          ("%s", srt_getlasterror_str ()));
      break;
    }

    rest = MIN (mapinfo->size - len, payload_size);

    sent = srt_sendmsg2 (wsock, (char *) (msg + len), rest, 0);
    if (sent < 0) {
      GST_ELEMENT_ERROR (srtobject->element, RESOURCE, WRITE, NULL,
          ("%s", srt_getlasterror_str ()));
      break;
    }
    len += sent;
  }

  return len;
}

gssize
gst_srt_object_write (GstSRTObject * srtobject,
    GstBufferList * headers,
    const GstMapInfo * mapinfo, GCancellable * cancellable, GError ** error)
{
  gssize len = 0;
  GstSRTConnectionMode connection_mode = GST_SRT_CONNECTION_MODE_NONE;
  gboolean wait_for_connection;

  /* Only sink element can write data */
  g_return_val_if_fail (gst_uri_handler_get_uri_type (GST_URI_HANDLER
          (srtobject->element)) == GST_URI_SINK, -1);

  GST_OBJECT_LOCK (srtobject->element);
  gst_structure_get_enum (srtobject->parameters, "mode",
      GST_TYPE_SRT_CONNECTION_MODE, (gint *) & connection_mode);
  wait_for_connection = srtobject->wait_for_connection;
  GST_OBJECT_UNLOCK (srtobject->element);

  if (connection_mode == GST_SRT_CONNECTION_MODE_LISTENER) {
    if (wait_for_connection) {
      if (!gst_srt_object_wait_caller (srtobject, cancellable, error))
        return -1;
    }
    len =
        gst_srt_object_write_to_callers (srtobject, headers, mapinfo,
        cancellable, error);
  } else {
    len =
        gst_srt_object_write_one (srtobject, headers, mapinfo, cancellable,
        error);
  }

  return len;
}

static GstStructure *
get_stats_for_srtsock (SRTSOCKET srtsock, gboolean is_sender, guint64 * bytes)
{
  GstStructure *s = gst_structure_new_empty ("application/x-srt-statistics");
  int ret;
  SRT_TRACEBSTATS stats;

  ret = srt_bstats (srtsock, &stats, 0);

  if (ret >= 0) {
    if (is_sender) {
      gst_structure_set (s,
          /* number of sent data packets, including retransmissions */
          "packets-sent", G_TYPE_INT64, stats.pktSent,
          /* number of lost packets (sender side) */
          "packets-sent-lost", G_TYPE_INT, stats.pktSndLoss,
          /* number of retransmitted packets */
          "packets-retransmitted", G_TYPE_INT, stats.pktRetrans,
          /* number of received ACK packets */
          "packet-ack-received", G_TYPE_INT, stats.pktRecvACK,
          /* number of received NAK packets */
          "packet-nack-received", G_TYPE_INT, stats.pktRecvNAK,
          /* time duration when UDT is sending data (idle time exclusive) */
          "send-duration-us", G_TYPE_INT64, stats.usSndDuration,
          /* number of sent data bytes, including retransmissions */
          "bytes-sent", G_TYPE_UINT64, stats.byteSent,
          /* number of retransmitted bytes */
          "bytes-retransmitted", G_TYPE_UINT64, stats.byteRetrans,
          /* number of too-late-to-send dropped bytes */
          "bytes-sent-dropped", G_TYPE_UINT64, stats.byteSndDrop,
          /* number of too-late-to-send dropped packets */
          "packets-sent-dropped", G_TYPE_INT, stats.pktSndDrop,
          /* sending rate in Mb/s */
          "send-rate-mbps", G_TYPE_DOUBLE, stats.mbpsSendRate,
          /* busy sending time (i.e., idle time exclusive) */
          "send-duration-us", G_TYPE_UINT64, stats.usSndDuration,
          "negotiated-latency-ms", G_TYPE_INT, stats.msSndTsbPdDelay, NULL);
      *bytes += stats.byteSent;
    } else {
      gst_structure_set (s,
          "packets-received", G_TYPE_INT64, stats.pktRecvTotal,
          "packets-received-lost", G_TYPE_INT, stats.pktRcvLossTotal,
          /* number of sent ACK packets */
          "packet-ack-sent", G_TYPE_INT, stats.pktSentACK,
          /* number of sent NAK packets */
          "packet-nack-sent", G_TYPE_INT, stats.pktSentNAK,
          "bytes-received", G_TYPE_UINT64, stats.byteRecvTotal,
          "bytes-received-lost", G_TYPE_UINT64, stats.byteRcvLossTotal,
          "receive-rate-mbps", G_TYPE_DOUBLE, stats.mbpsRecvRate,
          "negotiated-latency-ms", G_TYPE_INT, stats.msRcvTsbPdDelay, NULL);
      *bytes += stats.byteRecvTotal;
    }

    gst_structure_set (s,
        /* estimated bandwidth, in Mb/s */
        "bandwidth-mbps", G_TYPE_DOUBLE, stats.mbpsBandwidth,
        "rtt-ms", G_TYPE_DOUBLE, stats.msRTT, NULL);

  }

  return s;
}

GstStructure *
gst_srt_object_get_stats (GstSRTObject * srtobject)
{
  GstStructure *s = NULL;
  gboolean is_sender = GST_IS_BASE_SINK (srtobject->element);
  guint64 bytes;

  g_mutex_lock (&srtobject->sock_lock);

  bytes = srtobject->previous_bytes;

  if (srtobject->sock != SRT_INVALID_SOCK) {
    s = get_stats_for_srtsock (srtobject->sock, is_sender, &bytes);
    goto done;
  }

  s = gst_structure_new_empty ("application/x-srt-statistics");

  if (srtobject->callers) {
    GValueArray *callers_stats = g_value_array_new (1);
    GValue callers_stats_v = G_VALUE_INIT;
    GList *item;

    for (item = srtobject->callers; item; item = item->next) {
      SRTCaller *caller = item->data;
      GstStructure *tmp;
      GValue *v;

      tmp = get_stats_for_srtsock (caller->sock, is_sender, &bytes);

      g_value_array_append (callers_stats, NULL);
      v = g_value_array_get_nth (callers_stats, callers_stats->n_values - 1);
      g_value_init (v, GST_TYPE_STRUCTURE);
      g_value_take_boxed (v, tmp);
    }

    g_value_init (&callers_stats_v, G_TYPE_VALUE_ARRAY);
    g_value_take_boxed (&callers_stats_v, callers_stats);
    gst_structure_take_value (s, "callers", &callers_stats_v);
  }

done:
  gst_structure_set (s, is_sender ? "bytes-sent-total" : "bytes-received-total",
      G_TYPE_UINT64, bytes, NULL);

  g_mutex_unlock (&srtobject->sock_lock);

  return s;
}

static GstStructure *
gst_srt_object_accumulate_stats (GstSRTObject * srtobject, SRTSOCKET srtsock)
{
  gboolean is_sender = GST_IS_BASE_SINK (srtobject->element);
  GstStructure *stats;
  guint64 bytes = 0;

  stats = get_stats_for_srtsock (srtsock, is_sender, &bytes);
  srtobject->previous_bytes += bytes;

  return stats;
}
