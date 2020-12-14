
/* This file is generated by glib-mkenums, do not modify it. This code is licensed under the same license as the containing project. Note that it links to GLib, so must comply with the LGPL linking clauses. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "gstrtsp-enumtypes.h"
#include "gstrtspconnection.h"
#include "gstrtspdefs.h"
#include "gstrtspextension.h"
#include "gstrtsp.h"
#include "gstrtspmessage.h"
#include "gstrtsprange.h"
#include "gstrtsptransport.h"
#include "gstrtspurl.h"
#include "rtsp-prelude.h"
#include "rtsp.h"

#define C_ENUM(v) ((gint) v)
#define C_FLAGS(v) ((guint) v)

/* enumerations from "gstrtspdefs.h" */

GType
gst_rtsp_result_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_RTSP_OK), "GST_RTSP_OK", "ok" },
    { C_ENUM(GST_RTSP_ERROR), "GST_RTSP_ERROR", "error" },
    { C_ENUM(GST_RTSP_EINVAL), "GST_RTSP_EINVAL", "einval" },
    { C_ENUM(GST_RTSP_EINTR), "GST_RTSP_EINTR", "eintr" },
    { C_ENUM(GST_RTSP_ENOMEM), "GST_RTSP_ENOMEM", "enomem" },
    { C_ENUM(GST_RTSP_ERESOLV), "GST_RTSP_ERESOLV", "eresolv" },
    { C_ENUM(GST_RTSP_ENOTIMPL), "GST_RTSP_ENOTIMPL", "enotimpl" },
    { C_ENUM(GST_RTSP_ESYS), "GST_RTSP_ESYS", "esys" },
    { C_ENUM(GST_RTSP_EPARSE), "GST_RTSP_EPARSE", "eparse" },
    { C_ENUM(GST_RTSP_EWSASTART), "GST_RTSP_EWSASTART", "ewsastart" },
    { C_ENUM(GST_RTSP_EWSAVERSION), "GST_RTSP_EWSAVERSION", "ewsaversion" },
    { C_ENUM(GST_RTSP_EEOF), "GST_RTSP_EEOF", "eeof" },
    { C_ENUM(GST_RTSP_ENET), "GST_RTSP_ENET", "enet" },
    { C_ENUM(GST_RTSP_ENOTIP), "GST_RTSP_ENOTIP", "enotip" },
    { C_ENUM(GST_RTSP_ETIMEOUT), "GST_RTSP_ETIMEOUT", "etimeout" },
    { C_ENUM(GST_RTSP_ETGET), "GST_RTSP_ETGET", "etget" },
    { C_ENUM(GST_RTSP_ETPOST), "GST_RTSP_ETPOST", "etpost" },
    { C_ENUM(GST_RTSP_ELAST), "GST_RTSP_ELAST", "elast" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstRTSPResult"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_rtsp_event_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GFlagsValue values[] = {
    { C_FLAGS(GST_RTSP_EV_READ), "GST_RTSP_EV_READ", "read" },
    { C_FLAGS(GST_RTSP_EV_WRITE), "GST_RTSP_EV_WRITE", "write" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_flags_register_static (g_intern_static_string ("GstRTSPEvent"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_rtsp_family_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_RTSP_FAM_NONE), "GST_RTSP_FAM_NONE", "none" },
    { C_ENUM(GST_RTSP_FAM_INET), "GST_RTSP_FAM_INET", "inet" },
    { C_ENUM(GST_RTSP_FAM_INET6), "GST_RTSP_FAM_INET6", "inet6" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstRTSPFamily"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_rtsp_state_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_RTSP_STATE_INVALID), "GST_RTSP_STATE_INVALID", "invalid" },
    { C_ENUM(GST_RTSP_STATE_INIT), "GST_RTSP_STATE_INIT", "init" },
    { C_ENUM(GST_RTSP_STATE_READY), "GST_RTSP_STATE_READY", "ready" },
    { C_ENUM(GST_RTSP_STATE_SEEKING), "GST_RTSP_STATE_SEEKING", "seeking" },
    { C_ENUM(GST_RTSP_STATE_PLAYING), "GST_RTSP_STATE_PLAYING", "playing" },
    { C_ENUM(GST_RTSP_STATE_RECORDING), "GST_RTSP_STATE_RECORDING", "recording" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstRTSPState"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_rtsp_version_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_RTSP_VERSION_INVALID), "GST_RTSP_VERSION_INVALID", "invalid" },
    { C_ENUM(GST_RTSP_VERSION_1_0), "GST_RTSP_VERSION_1_0", "1-0" },
    { C_ENUM(GST_RTSP_VERSION_1_1), "GST_RTSP_VERSION_1_1", "1-1" },
    { C_ENUM(GST_RTSP_VERSION_2_0), "GST_RTSP_VERSION_2_0", "2-0" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstRTSPVersion"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_rtsp_method_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GFlagsValue values[] = {
    { C_FLAGS(GST_RTSP_INVALID), "GST_RTSP_INVALID", "invalid" },
    { C_FLAGS(GST_RTSP_DESCRIBE), "GST_RTSP_DESCRIBE", "describe" },
    { C_FLAGS(GST_RTSP_ANNOUNCE), "GST_RTSP_ANNOUNCE", "announce" },
    { C_FLAGS(GST_RTSP_GET_PARAMETER), "GST_RTSP_GET_PARAMETER", "get-parameter" },
    { C_FLAGS(GST_RTSP_OPTIONS), "GST_RTSP_OPTIONS", "options" },
    { C_FLAGS(GST_RTSP_PAUSE), "GST_RTSP_PAUSE", "pause" },
    { C_FLAGS(GST_RTSP_PLAY), "GST_RTSP_PLAY", "play" },
    { C_FLAGS(GST_RTSP_RECORD), "GST_RTSP_RECORD", "record" },
    { C_FLAGS(GST_RTSP_REDIRECT), "GST_RTSP_REDIRECT", "redirect" },
    { C_FLAGS(GST_RTSP_SETUP), "GST_RTSP_SETUP", "setup" },
    { C_FLAGS(GST_RTSP_SET_PARAMETER), "GST_RTSP_SET_PARAMETER", "set-parameter" },
    { C_FLAGS(GST_RTSP_TEARDOWN), "GST_RTSP_TEARDOWN", "teardown" },
    { C_FLAGS(GST_RTSP_GET), "GST_RTSP_GET", "get" },
    { C_FLAGS(GST_RTSP_POST), "GST_RTSP_POST", "post" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_flags_register_static (g_intern_static_string ("GstRTSPMethod"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_rtsp_auth_method_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_RTSP_AUTH_NONE), "GST_RTSP_AUTH_NONE", "none" },
    { C_ENUM(GST_RTSP_AUTH_BASIC), "GST_RTSP_AUTH_BASIC", "basic" },
    { C_ENUM(GST_RTSP_AUTH_DIGEST), "GST_RTSP_AUTH_DIGEST", "digest" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstRTSPAuthMethod"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_rtsp_header_field_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_RTSP_HDR_INVALID), "GST_RTSP_HDR_INVALID", "invalid" },
    { C_ENUM(GST_RTSP_HDR_ACCEPT), "GST_RTSP_HDR_ACCEPT", "accept" },
    { C_ENUM(GST_RTSP_HDR_ACCEPT_ENCODING), "GST_RTSP_HDR_ACCEPT_ENCODING", "accept-encoding" },
    { C_ENUM(GST_RTSP_HDR_ACCEPT_LANGUAGE), "GST_RTSP_HDR_ACCEPT_LANGUAGE", "accept-language" },
    { C_ENUM(GST_RTSP_HDR_ALLOW), "GST_RTSP_HDR_ALLOW", "allow" },
    { C_ENUM(GST_RTSP_HDR_AUTHORIZATION), "GST_RTSP_HDR_AUTHORIZATION", "authorization" },
    { C_ENUM(GST_RTSP_HDR_BANDWIDTH), "GST_RTSP_HDR_BANDWIDTH", "bandwidth" },
    { C_ENUM(GST_RTSP_HDR_BLOCKSIZE), "GST_RTSP_HDR_BLOCKSIZE", "blocksize" },
    { C_ENUM(GST_RTSP_HDR_CACHE_CONTROL), "GST_RTSP_HDR_CACHE_CONTROL", "cache-control" },
    { C_ENUM(GST_RTSP_HDR_CONFERENCE), "GST_RTSP_HDR_CONFERENCE", "conference" },
    { C_ENUM(GST_RTSP_HDR_CONNECTION), "GST_RTSP_HDR_CONNECTION", "connection" },
    { C_ENUM(GST_RTSP_HDR_CONTENT_BASE), "GST_RTSP_HDR_CONTENT_BASE", "content-base" },
    { C_ENUM(GST_RTSP_HDR_CONTENT_ENCODING), "GST_RTSP_HDR_CONTENT_ENCODING", "content-encoding" },
    { C_ENUM(GST_RTSP_HDR_CONTENT_LANGUAGE), "GST_RTSP_HDR_CONTENT_LANGUAGE", "content-language" },
    { C_ENUM(GST_RTSP_HDR_CONTENT_LENGTH), "GST_RTSP_HDR_CONTENT_LENGTH", "content-length" },
    { C_ENUM(GST_RTSP_HDR_CONTENT_LOCATION), "GST_RTSP_HDR_CONTENT_LOCATION", "content-location" },
    { C_ENUM(GST_RTSP_HDR_CONTENT_TYPE), "GST_RTSP_HDR_CONTENT_TYPE", "content-type" },
    { C_ENUM(GST_RTSP_HDR_CSEQ), "GST_RTSP_HDR_CSEQ", "cseq" },
    { C_ENUM(GST_RTSP_HDR_DATE), "GST_RTSP_HDR_DATE", "date" },
    { C_ENUM(GST_RTSP_HDR_EXPIRES), "GST_RTSP_HDR_EXPIRES", "expires" },
    { C_ENUM(GST_RTSP_HDR_FROM), "GST_RTSP_HDR_FROM", "from" },
    { C_ENUM(GST_RTSP_HDR_IF_MODIFIED_SINCE), "GST_RTSP_HDR_IF_MODIFIED_SINCE", "if-modified-since" },
    { C_ENUM(GST_RTSP_HDR_LAST_MODIFIED), "GST_RTSP_HDR_LAST_MODIFIED", "last-modified" },
    { C_ENUM(GST_RTSP_HDR_PROXY_AUTHENTICATE), "GST_RTSP_HDR_PROXY_AUTHENTICATE", "proxy-authenticate" },
    { C_ENUM(GST_RTSP_HDR_PROXY_REQUIRE), "GST_RTSP_HDR_PROXY_REQUIRE", "proxy-require" },
    { C_ENUM(GST_RTSP_HDR_PUBLIC), "GST_RTSP_HDR_PUBLIC", "public" },
    { C_ENUM(GST_RTSP_HDR_RANGE), "GST_RTSP_HDR_RANGE", "range" },
    { C_ENUM(GST_RTSP_HDR_REFERER), "GST_RTSP_HDR_REFERER", "referer" },
    { C_ENUM(GST_RTSP_HDR_REQUIRE), "GST_RTSP_HDR_REQUIRE", "require" },
    { C_ENUM(GST_RTSP_HDR_RETRY_AFTER), "GST_RTSP_HDR_RETRY_AFTER", "retry-after" },
    { C_ENUM(GST_RTSP_HDR_RTP_INFO), "GST_RTSP_HDR_RTP_INFO", "rtp-info" },
    { C_ENUM(GST_RTSP_HDR_SCALE), "GST_RTSP_HDR_SCALE", "scale" },
    { C_ENUM(GST_RTSP_HDR_SESSION), "GST_RTSP_HDR_SESSION", "session" },
    { C_ENUM(GST_RTSP_HDR_SERVER), "GST_RTSP_HDR_SERVER", "server" },
    { C_ENUM(GST_RTSP_HDR_SPEED), "GST_RTSP_HDR_SPEED", "speed" },
    { C_ENUM(GST_RTSP_HDR_TRANSPORT), "GST_RTSP_HDR_TRANSPORT", "transport" },
    { C_ENUM(GST_RTSP_HDR_UNSUPPORTED), "GST_RTSP_HDR_UNSUPPORTED", "unsupported" },
    { C_ENUM(GST_RTSP_HDR_USER_AGENT), "GST_RTSP_HDR_USER_AGENT", "user-agent" },
    { C_ENUM(GST_RTSP_HDR_VIA), "GST_RTSP_HDR_VIA", "via" },
    { C_ENUM(GST_RTSP_HDR_WWW_AUTHENTICATE), "GST_RTSP_HDR_WWW_AUTHENTICATE", "www-authenticate" },
    { C_ENUM(GST_RTSP_HDR_CLIENT_CHALLENGE), "GST_RTSP_HDR_CLIENT_CHALLENGE", "client-challenge" },
    { C_ENUM(GST_RTSP_HDR_REAL_CHALLENGE1), "GST_RTSP_HDR_REAL_CHALLENGE1", "real-challenge1" },
    { C_ENUM(GST_RTSP_HDR_REAL_CHALLENGE2), "GST_RTSP_HDR_REAL_CHALLENGE2", "real-challenge2" },
    { C_ENUM(GST_RTSP_HDR_REAL_CHALLENGE3), "GST_RTSP_HDR_REAL_CHALLENGE3", "real-challenge3" },
    { C_ENUM(GST_RTSP_HDR_SUBSCRIBE), "GST_RTSP_HDR_SUBSCRIBE", "subscribe" },
    { C_ENUM(GST_RTSP_HDR_ALERT), "GST_RTSP_HDR_ALERT", "alert" },
    { C_ENUM(GST_RTSP_HDR_CLIENT_ID), "GST_RTSP_HDR_CLIENT_ID", "client-id" },
    { C_ENUM(GST_RTSP_HDR_COMPANY_ID), "GST_RTSP_HDR_COMPANY_ID", "company-id" },
    { C_ENUM(GST_RTSP_HDR_GUID), "GST_RTSP_HDR_GUID", "guid" },
    { C_ENUM(GST_RTSP_HDR_REGION_DATA), "GST_RTSP_HDR_REGION_DATA", "region-data" },
    { C_ENUM(GST_RTSP_HDR_MAX_ASM_WIDTH), "GST_RTSP_HDR_MAX_ASM_WIDTH", "max-asm-width" },
    { C_ENUM(GST_RTSP_HDR_LANGUAGE), "GST_RTSP_HDR_LANGUAGE", "language" },
    { C_ENUM(GST_RTSP_HDR_PLAYER_START_TIME), "GST_RTSP_HDR_PLAYER_START_TIME", "player-start-time" },
    { C_ENUM(GST_RTSP_HDR_LOCATION), "GST_RTSP_HDR_LOCATION", "location" },
    { C_ENUM(GST_RTSP_HDR_ETAG), "GST_RTSP_HDR_ETAG", "etag" },
    { C_ENUM(GST_RTSP_HDR_IF_MATCH), "GST_RTSP_HDR_IF_MATCH", "if-match" },
    { C_ENUM(GST_RTSP_HDR_ACCEPT_CHARSET), "GST_RTSP_HDR_ACCEPT_CHARSET", "accept-charset" },
    { C_ENUM(GST_RTSP_HDR_SUPPORTED), "GST_RTSP_HDR_SUPPORTED", "supported" },
    { C_ENUM(GST_RTSP_HDR_VARY), "GST_RTSP_HDR_VARY", "vary" },
    { C_ENUM(GST_RTSP_HDR_X_ACCELERATE_STREAMING), "GST_RTSP_HDR_X_ACCELERATE_STREAMING", "x-accelerate-streaming" },
    { C_ENUM(GST_RTSP_HDR_X_ACCEPT_AUTHENT), "GST_RTSP_HDR_X_ACCEPT_AUTHENT", "x-accept-authent" },
    { C_ENUM(GST_RTSP_HDR_X_ACCEPT_PROXY_AUTHENT), "GST_RTSP_HDR_X_ACCEPT_PROXY_AUTHENT", "x-accept-proxy-authent" },
    { C_ENUM(GST_RTSP_HDR_X_BROADCAST_ID), "GST_RTSP_HDR_X_BROADCAST_ID", "x-broadcast-id" },
    { C_ENUM(GST_RTSP_HDR_X_BURST_STREAMING), "GST_RTSP_HDR_X_BURST_STREAMING", "x-burst-streaming" },
    { C_ENUM(GST_RTSP_HDR_X_NOTICE), "GST_RTSP_HDR_X_NOTICE", "x-notice" },
    { C_ENUM(GST_RTSP_HDR_X_PLAYER_LAG_TIME), "GST_RTSP_HDR_X_PLAYER_LAG_TIME", "x-player-lag-time" },
    { C_ENUM(GST_RTSP_HDR_X_PLAYLIST), "GST_RTSP_HDR_X_PLAYLIST", "x-playlist" },
    { C_ENUM(GST_RTSP_HDR_X_PLAYLIST_CHANGE_NOTICE), "GST_RTSP_HDR_X_PLAYLIST_CHANGE_NOTICE", "x-playlist-change-notice" },
    { C_ENUM(GST_RTSP_HDR_X_PLAYLIST_GEN_ID), "GST_RTSP_HDR_X_PLAYLIST_GEN_ID", "x-playlist-gen-id" },
    { C_ENUM(GST_RTSP_HDR_X_PLAYLIST_SEEK_ID), "GST_RTSP_HDR_X_PLAYLIST_SEEK_ID", "x-playlist-seek-id" },
    { C_ENUM(GST_RTSP_HDR_X_PROXY_CLIENT_AGENT), "GST_RTSP_HDR_X_PROXY_CLIENT_AGENT", "x-proxy-client-agent" },
    { C_ENUM(GST_RTSP_HDR_X_PROXY_CLIENT_VERB), "GST_RTSP_HDR_X_PROXY_CLIENT_VERB", "x-proxy-client-verb" },
    { C_ENUM(GST_RTSP_HDR_X_RECEDING_PLAYLISTCHANGE), "GST_RTSP_HDR_X_RECEDING_PLAYLISTCHANGE", "x-receding-playlistchange" },
    { C_ENUM(GST_RTSP_HDR_X_RTP_INFO), "GST_RTSP_HDR_X_RTP_INFO", "x-rtp-info" },
    { C_ENUM(GST_RTSP_HDR_X_STARTUPPROFILE), "GST_RTSP_HDR_X_STARTUPPROFILE", "x-startupprofile" },
    { C_ENUM(GST_RTSP_HDR_TIMESTAMP), "GST_RTSP_HDR_TIMESTAMP", "timestamp" },
    { C_ENUM(GST_RTSP_HDR_AUTHENTICATION_INFO), "GST_RTSP_HDR_AUTHENTICATION_INFO", "authentication-info" },
    { C_ENUM(GST_RTSP_HDR_HOST), "GST_RTSP_HDR_HOST", "host" },
    { C_ENUM(GST_RTSP_HDR_PRAGMA), "GST_RTSP_HDR_PRAGMA", "pragma" },
    { C_ENUM(GST_RTSP_HDR_X_SERVER_IP_ADDRESS), "GST_RTSP_HDR_X_SERVER_IP_ADDRESS", "x-server-ip-address" },
    { C_ENUM(GST_RTSP_HDR_X_SESSIONCOOKIE), "GST_RTSP_HDR_X_SESSIONCOOKIE", "x-sessioncookie" },
    { C_ENUM(GST_RTSP_HDR_RTCP_INTERVAL), "GST_RTSP_HDR_RTCP_INTERVAL", "rtcp-interval" },
    { C_ENUM(GST_RTSP_HDR_KEYMGMT), "GST_RTSP_HDR_KEYMGMT", "keymgmt" },
    { C_ENUM(GST_RTSP_HDR_PIPELINED_REQUESTS), "GST_RTSP_HDR_PIPELINED_REQUESTS", "pipelined-requests" },
    { C_ENUM(GST_RTSP_HDR_MEDIA_PROPERTIES), "GST_RTSP_HDR_MEDIA_PROPERTIES", "media-properties" },
    { C_ENUM(GST_RTSP_HDR_SEEK_STYLE), "GST_RTSP_HDR_SEEK_STYLE", "seek-style" },
    { C_ENUM(GST_RTSP_HDR_ACCEPT_RANGES), "GST_RTSP_HDR_ACCEPT_RANGES", "accept-ranges" },
    { C_ENUM(GST_RTSP_HDR_FRAMES), "GST_RTSP_HDR_FRAMES", "frames" },
    { C_ENUM(GST_RTSP_HDR_RATE_CONTROL), "GST_RTSP_HDR_RATE_CONTROL", "rate-control" },
    { C_ENUM(GST_RTSP_HDR_LAST), "GST_RTSP_HDR_LAST", "last" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstRTSPHeaderField"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_rtsp_status_code_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_RTSP_STS_INVALID), "GST_RTSP_STS_INVALID", "invalid" },
    { C_ENUM(GST_RTSP_STS_CONTINUE), "GST_RTSP_STS_CONTINUE", "continue" },
    { C_ENUM(GST_RTSP_STS_OK), "GST_RTSP_STS_OK", "ok" },
    { C_ENUM(GST_RTSP_STS_CREATED), "GST_RTSP_STS_CREATED", "created" },
    { C_ENUM(GST_RTSP_STS_LOW_ON_STORAGE), "GST_RTSP_STS_LOW_ON_STORAGE", "low-on-storage" },
    { C_ENUM(GST_RTSP_STS_MULTIPLE_CHOICES), "GST_RTSP_STS_MULTIPLE_CHOICES", "multiple-choices" },
    { C_ENUM(GST_RTSP_STS_MOVED_PERMANENTLY), "GST_RTSP_STS_MOVED_PERMANENTLY", "moved-permanently" },
    { C_ENUM(GST_RTSP_STS_MOVE_TEMPORARILY), "GST_RTSP_STS_MOVE_TEMPORARILY", "move-temporarily" },
    { C_ENUM(GST_RTSP_STS_SEE_OTHER), "GST_RTSP_STS_SEE_OTHER", "see-other" },
    { C_ENUM(GST_RTSP_STS_NOT_MODIFIED), "GST_RTSP_STS_NOT_MODIFIED", "not-modified" },
    { C_ENUM(GST_RTSP_STS_USE_PROXY), "GST_RTSP_STS_USE_PROXY", "use-proxy" },
    { C_ENUM(GST_RTSP_STS_BAD_REQUEST), "GST_RTSP_STS_BAD_REQUEST", "bad-request" },
    { C_ENUM(GST_RTSP_STS_UNAUTHORIZED), "GST_RTSP_STS_UNAUTHORIZED", "unauthorized" },
    { C_ENUM(GST_RTSP_STS_PAYMENT_REQUIRED), "GST_RTSP_STS_PAYMENT_REQUIRED", "payment-required" },
    { C_ENUM(GST_RTSP_STS_FORBIDDEN), "GST_RTSP_STS_FORBIDDEN", "forbidden" },
    { C_ENUM(GST_RTSP_STS_NOT_FOUND), "GST_RTSP_STS_NOT_FOUND", "not-found" },
    { C_ENUM(GST_RTSP_STS_METHOD_NOT_ALLOWED), "GST_RTSP_STS_METHOD_NOT_ALLOWED", "method-not-allowed" },
    { C_ENUM(GST_RTSP_STS_NOT_ACCEPTABLE), "GST_RTSP_STS_NOT_ACCEPTABLE", "not-acceptable" },
    { C_ENUM(GST_RTSP_STS_PROXY_AUTH_REQUIRED), "GST_RTSP_STS_PROXY_AUTH_REQUIRED", "proxy-auth-required" },
    { C_ENUM(GST_RTSP_STS_REQUEST_TIMEOUT), "GST_RTSP_STS_REQUEST_TIMEOUT", "request-timeout" },
    { C_ENUM(GST_RTSP_STS_GONE), "GST_RTSP_STS_GONE", "gone" },
    { C_ENUM(GST_RTSP_STS_LENGTH_REQUIRED), "GST_RTSP_STS_LENGTH_REQUIRED", "length-required" },
    { C_ENUM(GST_RTSP_STS_PRECONDITION_FAILED), "GST_RTSP_STS_PRECONDITION_FAILED", "precondition-failed" },
    { C_ENUM(GST_RTSP_STS_REQUEST_ENTITY_TOO_LARGE), "GST_RTSP_STS_REQUEST_ENTITY_TOO_LARGE", "request-entity-too-large" },
    { C_ENUM(GST_RTSP_STS_REQUEST_URI_TOO_LARGE), "GST_RTSP_STS_REQUEST_URI_TOO_LARGE", "request-uri-too-large" },
    { C_ENUM(GST_RTSP_STS_UNSUPPORTED_MEDIA_TYPE), "GST_RTSP_STS_UNSUPPORTED_MEDIA_TYPE", "unsupported-media-type" },
    { C_ENUM(GST_RTSP_STS_PARAMETER_NOT_UNDERSTOOD), "GST_RTSP_STS_PARAMETER_NOT_UNDERSTOOD", "parameter-not-understood" },
    { C_ENUM(GST_RTSP_STS_CONFERENCE_NOT_FOUND), "GST_RTSP_STS_CONFERENCE_NOT_FOUND", "conference-not-found" },
    { C_ENUM(GST_RTSP_STS_NOT_ENOUGH_BANDWIDTH), "GST_RTSP_STS_NOT_ENOUGH_BANDWIDTH", "not-enough-bandwidth" },
    { C_ENUM(GST_RTSP_STS_SESSION_NOT_FOUND), "GST_RTSP_STS_SESSION_NOT_FOUND", "session-not-found" },
    { C_ENUM(GST_RTSP_STS_METHOD_NOT_VALID_IN_THIS_STATE), "GST_RTSP_STS_METHOD_NOT_VALID_IN_THIS_STATE", "method-not-valid-in-this-state" },
    { C_ENUM(GST_RTSP_STS_HEADER_FIELD_NOT_VALID_FOR_RESOURCE), "GST_RTSP_STS_HEADER_FIELD_NOT_VALID_FOR_RESOURCE", "header-field-not-valid-for-resource" },
    { C_ENUM(GST_RTSP_STS_INVALID_RANGE), "GST_RTSP_STS_INVALID_RANGE", "invalid-range" },
    { C_ENUM(GST_RTSP_STS_PARAMETER_IS_READONLY), "GST_RTSP_STS_PARAMETER_IS_READONLY", "parameter-is-readonly" },
    { C_ENUM(GST_RTSP_STS_AGGREGATE_OPERATION_NOT_ALLOWED), "GST_RTSP_STS_AGGREGATE_OPERATION_NOT_ALLOWED", "aggregate-operation-not-allowed" },
    { C_ENUM(GST_RTSP_STS_ONLY_AGGREGATE_OPERATION_ALLOWED), "GST_RTSP_STS_ONLY_AGGREGATE_OPERATION_ALLOWED", "only-aggregate-operation-allowed" },
    { C_ENUM(GST_RTSP_STS_UNSUPPORTED_TRANSPORT), "GST_RTSP_STS_UNSUPPORTED_TRANSPORT", "unsupported-transport" },
    { C_ENUM(GST_RTSP_STS_DESTINATION_UNREACHABLE), "GST_RTSP_STS_DESTINATION_UNREACHABLE", "destination-unreachable" },
    { C_ENUM(GST_RTSP_STS_KEY_MANAGEMENT_FAILURE), "GST_RTSP_STS_KEY_MANAGEMENT_FAILURE", "key-management-failure" },
    { C_ENUM(GST_RTSP_STS_INTERNAL_SERVER_ERROR), "GST_RTSP_STS_INTERNAL_SERVER_ERROR", "internal-server-error" },
    { C_ENUM(GST_RTSP_STS_NOT_IMPLEMENTED), "GST_RTSP_STS_NOT_IMPLEMENTED", "not-implemented" },
    { C_ENUM(GST_RTSP_STS_BAD_GATEWAY), "GST_RTSP_STS_BAD_GATEWAY", "bad-gateway" },
    { C_ENUM(GST_RTSP_STS_SERVICE_UNAVAILABLE), "GST_RTSP_STS_SERVICE_UNAVAILABLE", "service-unavailable" },
    { C_ENUM(GST_RTSP_STS_GATEWAY_TIMEOUT), "GST_RTSP_STS_GATEWAY_TIMEOUT", "gateway-timeout" },
    { C_ENUM(GST_RTSP_STS_RTSP_VERSION_NOT_SUPPORTED), "GST_RTSP_STS_RTSP_VERSION_NOT_SUPPORTED", "rtsp-version-not-supported" },
    { C_ENUM(GST_RTSP_STS_OPTION_NOT_SUPPORTED), "GST_RTSP_STS_OPTION_NOT_SUPPORTED", "option-not-supported" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstRTSPStatusCode"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

/* enumerations from "gstrtspmessage.h" */

GType
gst_rtsp_msg_type_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_RTSP_MESSAGE_INVALID), "GST_RTSP_MESSAGE_INVALID", "invalid" },
    { C_ENUM(GST_RTSP_MESSAGE_REQUEST), "GST_RTSP_MESSAGE_REQUEST", "request" },
    { C_ENUM(GST_RTSP_MESSAGE_RESPONSE), "GST_RTSP_MESSAGE_RESPONSE", "response" },
    { C_ENUM(GST_RTSP_MESSAGE_HTTP_REQUEST), "GST_RTSP_MESSAGE_HTTP_REQUEST", "http-request" },
    { C_ENUM(GST_RTSP_MESSAGE_HTTP_RESPONSE), "GST_RTSP_MESSAGE_HTTP_RESPONSE", "http-response" },
    { C_ENUM(GST_RTSP_MESSAGE_DATA), "GST_RTSP_MESSAGE_DATA", "data" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstRTSPMsgType"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

/* enumerations from "gstrtsprange.h" */

GType
gst_rtsp_range_unit_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_RTSP_RANGE_SMPTE), "GST_RTSP_RANGE_SMPTE", "smpte" },
    { C_ENUM(GST_RTSP_RANGE_SMPTE_30_DROP), "GST_RTSP_RANGE_SMPTE_30_DROP", "smpte-30-drop" },
    { C_ENUM(GST_RTSP_RANGE_SMPTE_25), "GST_RTSP_RANGE_SMPTE_25", "smpte-25" },
    { C_ENUM(GST_RTSP_RANGE_NPT), "GST_RTSP_RANGE_NPT", "npt" },
    { C_ENUM(GST_RTSP_RANGE_CLOCK), "GST_RTSP_RANGE_CLOCK", "clock" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstRTSPRangeUnit"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_rtsp_time_type_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_RTSP_TIME_SECONDS), "GST_RTSP_TIME_SECONDS", "seconds" },
    { C_ENUM(GST_RTSP_TIME_NOW), "GST_RTSP_TIME_NOW", "now" },
    { C_ENUM(GST_RTSP_TIME_END), "GST_RTSP_TIME_END", "end" },
    { C_ENUM(GST_RTSP_TIME_FRAMES), "GST_RTSP_TIME_FRAMES", "frames" },
    { C_ENUM(GST_RTSP_TIME_UTC), "GST_RTSP_TIME_UTC", "utc" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstRTSPTimeType"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

/* enumerations from "gstrtsptransport.h" */

GType
gst_rtsp_trans_mode_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GFlagsValue values[] = {
    { C_FLAGS(GST_RTSP_TRANS_UNKNOWN), "GST_RTSP_TRANS_UNKNOWN", "unknown" },
    { C_FLAGS(GST_RTSP_TRANS_RTP), "GST_RTSP_TRANS_RTP", "rtp" },
    { C_FLAGS(GST_RTSP_TRANS_RDT), "GST_RTSP_TRANS_RDT", "rdt" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_flags_register_static (g_intern_static_string ("GstRTSPTransMode"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_rtsp_profile_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GFlagsValue values[] = {
    { C_FLAGS(GST_RTSP_PROFILE_UNKNOWN), "GST_RTSP_PROFILE_UNKNOWN", "unknown" },
    { C_FLAGS(GST_RTSP_PROFILE_AVP), "GST_RTSP_PROFILE_AVP", "avp" },
    { C_FLAGS(GST_RTSP_PROFILE_SAVP), "GST_RTSP_PROFILE_SAVP", "savp" },
    { C_FLAGS(GST_RTSP_PROFILE_AVPF), "GST_RTSP_PROFILE_AVPF", "avpf" },
    { C_FLAGS(GST_RTSP_PROFILE_SAVPF), "GST_RTSP_PROFILE_SAVPF", "savpf" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_flags_register_static (g_intern_static_string ("GstRTSPProfile"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_rtsp_lower_trans_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GFlagsValue values[] = {
    { C_FLAGS(GST_RTSP_LOWER_TRANS_UNKNOWN), "GST_RTSP_LOWER_TRANS_UNKNOWN", "unknown" },
    { C_FLAGS(GST_RTSP_LOWER_TRANS_UDP), "GST_RTSP_LOWER_TRANS_UDP", "udp" },
    { C_FLAGS(GST_RTSP_LOWER_TRANS_UDP_MCAST), "GST_RTSP_LOWER_TRANS_UDP_MCAST", "udp-mcast" },
    { C_FLAGS(GST_RTSP_LOWER_TRANS_TCP), "GST_RTSP_LOWER_TRANS_TCP", "tcp" },
    { C_FLAGS(GST_RTSP_LOWER_TRANS_HTTP), "GST_RTSP_LOWER_TRANS_HTTP", "http" },
    { C_FLAGS(GST_RTSP_LOWER_TRANS_TLS), "GST_RTSP_LOWER_TRANS_TLS", "tls" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_flags_register_static (g_intern_static_string ("GstRTSPLowerTrans"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

/* Generated data ends here */

