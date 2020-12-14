/* A Bison parser, made by GNU Bison 3.7.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         priv_gst_parse_yyparse
#define yylex           priv_gst_parse_yylex
#define yyerror         priv_gst_parse_yyerror
#define yydebug         priv_gst_parse_yydebug
#define yynerrs         priv_gst_parse_yynerrs

/* First part of user prologue.  */
#line 1 "gst/parse/grammar.y"

#include "../gst_private.h"

#include <glib-object.h>
#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../gst-i18n-lib.h"

#include "../gstconfig.h"
#include "../gstparse.h"
#include "../gstinfo.h"
#include "../gsterror.h"
#include "../gststructure.h"
#include "../gsturi.h"
#include "../gstutils.h"
#include "../gstvalue.h"
#include "../gstchildproxy.h"
#include "types.h"

/* All error messages in this file are user-visible and need to be translated.
 * Don't start the message with a capital, and don't end them with a period,
 * as they will be presented inside a sentence/error.
 */

#define YYERROR_VERBOSE 1

#define YYENABLE_NLS 0

#ifndef YYLTYPE_IS_TRIVIAL
#define YYLTYPE_IS_TRIVIAL 0
#endif

/*******************************************************************************************
*** Tracing memory leaks
*******************************************************************************************/

#ifdef __GST_PARSE_TRACE
static guint __strings;
static guint __links;
static guint __chains;
gchar *
__gst_parse_strdup (gchar *org)
{
  gchar *ret;
  __strings++;
  ret = g_strdup (org);
  /* g_print ("ALLOCATED STR   (%3u): %p %s\n", __strings, ret, ret); */
  return ret;
}
void
__gst_parse_strfree (gchar *str)
{
  if (str) {
    /* g_print ("FREEING STR     (%3u): %p %s\n", __strings - 1, str, str); */
    g_free (str);
    g_return_if_fail (__strings > 0);
    __strings--;
  }
}
link_t *__gst_parse_link_new (void)
{
  link_t *ret;
  __links++;
  ret = g_slice_new0 (link_t);
  /* g_print ("ALLOCATED LINK  (%3u): %p\n", __links, ret); */
  return ret;
}
void
__gst_parse_link_free (link_t *data)
{
  if (data) {
    /* g_print ("FREEING LINK    (%3u): %p\n", __links - 1, data); */
    g_slice_free (link_t, data);
    g_return_if_fail (__links > 0);
    __links--;
  }
}
chain_t *
__gst_parse_chain_new (void)
{
  chain_t *ret;
  __chains++;
  ret = g_slice_new0 (chain_t);
  /* g_print ("@%p: ALLOCATED CHAIN (%3u):\n", ret, __chains); */
  return ret;
}
void
__gst_parse_chain_free (chain_t *data)
{
  /* g_print ("@%p: FREEING CHAIN   (%3u):\n", data, __chains - 1); */
  g_slice_free (chain_t, data);
  g_return_if_fail (__chains > 0);
  __chains--;
}

#endif /* __GST_PARSE_TRACE */

/*******************************************************************************************
*** define SET_ERROR macro/function
*******************************************************************************************/
#ifdef G_HAVE_ISO_VARARGS

#  define SET_ERROR(error, type, ...) \
G_STMT_START { \
  GST_CAT_ERROR (GST_CAT_PIPELINE, __VA_ARGS__); \
  if ((error) && !*(error)) { \
    g_set_error ((error), GST_PARSE_ERROR, (type), __VA_ARGS__); \
  } \
} G_STMT_END

#elif defined(G_HAVE_GNUC_VARARGS)

#  define SET_ERROR(error, type, args...) \
G_STMT_START { \
  GST_CAT_ERROR (GST_CAT_PIPELINE, args ); \
  if ((error) && !*(error)) { \
    g_set_error ((error), GST_PARSE_ERROR, (type), args ); \
  } \
} G_STMT_END

#else

static inline void
SET_ERROR (GError **error, gint type, const char *format, ...)
{
  if (error) {
    if (*error) {
      g_warning ("error while parsing");
    } else {
      va_list varargs;
      char *string;

      va_start (varargs, format);
      string = g_strdup_vprintf (format, varargs);
      va_end (varargs);

      g_set_error (error, GST_PARSE_ERROR, type, string);

      g_free (string);
    }
  }
}

#endif /* G_HAVE_ISO_VARARGS */

/*** define YYPRINTF macro/function if we're debugging */

/* bison 1.35 calls this macro with side effects, we need to make sure the
   side effects work - crappy bison */

#ifndef GST_DISABLE_GST_DEBUG
#  define YYDEBUG 1

#  ifdef G_HAVE_ISO_VARARGS

/* #  define YYFPRINTF(a, ...) GST_CAT_DEBUG (GST_CAT_PIPELINE, __VA_ARGS__) */
#    define YYFPRINTF(a, ...) \
G_STMT_START { \
     GST_CAT_LOG (GST_CAT_PIPELINE, __VA_ARGS__); \
} G_STMT_END

#  elif defined(G_HAVE_GNUC_VARARGS)

#    define YYFPRINTF(a, args...) \
G_STMT_START { \
     GST_CAT_LOG (GST_CAT_PIPELINE, args); \
} G_STMT_END

#  else

static inline void
YYPRINTF(const char *format, ...)
{
  va_list varargs;
  gchar *temp;

  va_start (varargs, format);
  temp = g_strdup_vprintf (format, varargs);
  GST_CAT_LOG (GST_CAT_PIPELINE, "%s", temp);
  g_free (temp);
  va_end (varargs);
}

#  endif /* G_HAVE_ISO_VARARGS */

#endif /* GST_DISABLE_GST_DEBUG */


/*
 * include headers generated by bison & flex, after defining (or not defining) YYDEBUG
 */
#include "grammar.tab.h"
#include "parse_lex.h"

/*******************************************************************************************
*** report missing elements/bins/..
*******************************************************************************************/


static void  add_missing_element(graph_t *graph,gchar *name){
  if ((graph)->ctx){
    (graph)->ctx->missing_elements = g_list_append ((graph)->ctx->missing_elements, g_strdup (name));
    }
}


/*******************************************************************************************
*** helpers for pipeline-setup
*******************************************************************************************/

#define TRY_SETUP_LINK(l) G_STMT_START { \
   if( (!(l)->src.element) && (!(l)->src.name) ){ \
     SET_ERROR (graph->error, GST_PARSE_ERROR_LINK, _("link has no source [sink=%s@%p]"), \
	(l)->sink.name ? (l)->sink.name : "", \
	(l)->sink.element); \
     gst_parse_free_link (l); \
   }else if( (!(l)->sink.element) && (!(l)->sink.name) ){ \
     SET_ERROR (graph->error, GST_PARSE_ERROR_LINK, _("link has no sink [source=%s@%p]"), \
	(l)->src.name ? (l)->src.name : "", \
	(l)->src.element); \
     gst_parse_free_link (l); \
   }else{ \
     graph->links = g_slist_append (graph->links, l ); \
   }   \
} G_STMT_END

typedef struct {
  gchar *src_pad;
  gchar *sink_pad;
  GstElement *sink;
  GstCaps *caps;
  gulong pad_added_signal_id, no_more_pads_signal_id;
  gboolean all_pads;
} DelayedLink;

typedef struct {
  gchar *name;
  gchar *value_str;
  gulong signal_id;
} DelayedSet;

static int  gst_resolve_reference(reference_t *rr, GstElement *pipeline){
  GstBin *bin;

  if(rr->element) return  0;  /* already resolved! */
  if(!rr->name)   return -2;  /* no chance! */

  if (GST_IS_BIN (pipeline)){
    bin = GST_BIN (pipeline);
    rr->element = gst_bin_get_by_name_recurse_up (bin, rr->name);
  } else {
    rr->element = strcmp (GST_ELEMENT_NAME (pipeline), rr->name) == 0 ?
		gst_object_ref(pipeline) : NULL;
  }
  if(rr->element) return 0; /* resolved */
  else            return -1; /* not found */
}

static void gst_parse_free_delayed_set (DelayedSet *set)
{
  g_free(set->name);
  g_free(set->value_str);
  g_slice_free(DelayedSet, set);
}

static void gst_parse_new_child(GstChildProxy *child_proxy, GObject *object,
    const gchar * name, gpointer data);

static void gst_parse_add_delayed_set (GstElement *element, gchar *name, gchar *value_str)
{
  DelayedSet *data = g_slice_new0 (DelayedSet);

  GST_CAT_LOG_OBJECT (GST_CAT_PIPELINE, element, "delaying property set %s to %s",
    name, value_str);

  data->name = g_strdup(name);
  data->value_str = g_strdup(value_str);
  data->signal_id = g_signal_connect_data(element, "child-added",
      G_CALLBACK (gst_parse_new_child), data, (GClosureNotify)
      gst_parse_free_delayed_set, (GConnectFlags) 0);

  /* FIXME: we would need to listen on all intermediate bins too */
  if (GST_IS_BIN (element)) {
    gchar **names, **current;
    GstElement *parent, *child;

    current = names = g_strsplit (name, "::", -1);
    parent = gst_bin_get_by_name (GST_BIN_CAST (element), current[0]);
    current++;
    while (parent && current[0]) {
      child = gst_bin_get_by_name (GST_BIN (parent), current[0]);
      if (!child && current[1]) {
        char *sub_name = g_strjoinv ("::", &current[0]);

        gst_parse_add_delayed_set(parent, sub_name, value_str);
        g_free (sub_name);
      }
      gst_object_unref (parent);
      parent = child;
      current++;
    }
    if (parent)
      gst_object_unref (parent);
    g_strfreev (names);
  }
}

static void gst_parse_new_child(GstChildProxy *child_proxy, GObject *object,
    const gchar * name, gpointer data)
{
  DelayedSet *set = (DelayedSet *) data;
  GParamSpec *pspec;
  GValue v = { 0, };
  GObject *target = NULL;
  GType value_type;

  GST_CAT_LOG_OBJECT (GST_CAT_PIPELINE, child_proxy, "new child %s, checking property %s",
      name, set->name);

  if (gst_child_proxy_lookup (child_proxy, set->name, &target, &pspec)) {
    gboolean got_value = FALSE;

    value_type = pspec->value_type;

    GST_CAT_LOG_OBJECT (GST_CAT_PIPELINE, child_proxy, "parsing delayed property %s as a %s from %s",
      pspec->name, g_type_name (value_type), set->value_str);
    g_value_init (&v, value_type);
    if (gst_value_deserialize (&v, set->value_str))
      got_value = TRUE;
    else if (g_type_is_a (value_type, GST_TYPE_ELEMENT)) {
       GstElement *bin;

       bin = gst_parse_bin_from_description_full (set->value_str, TRUE, NULL,
           GST_PARSE_FLAG_NO_SINGLE_ELEMENT_BINS | GST_PARSE_FLAG_PLACE_IN_BIN, NULL);
       if (bin) {
         g_value_set_object (&v, bin);
         got_value = TRUE;
       }
    }
    g_signal_handler_disconnect (child_proxy, set->signal_id);
    if (!got_value)
      goto error;
    g_object_set_property (target, pspec->name, &v);
  } else {
    const gchar *obj_name = GST_OBJECT_NAME(object);
    gint len = strlen (obj_name);

    /* do a delayed set */
    if ((strlen (set->name) > (len + 2)) && !strncmp (set->name, obj_name, len) && !strncmp (&set->name[len], "::", 2)) {
      gst_parse_add_delayed_set (GST_ELEMENT(child_proxy), set->name, set->value_str);
    }
  }

out:
  if (G_IS_VALUE (&v))
    g_value_unset (&v);
  if (target)
    gst_object_unref (target);
  return;

error:
  GST_CAT_ERROR (GST_CAT_PIPELINE, "could not set property \"%s\" in %"
      GST_PTR_FORMAT, pspec->name, target);
  goto out;
}

static void gst_parse_element_set (gchar *value, GstElement *element, graph_t *graph)
{
  GParamSpec *pspec = NULL;
  gchar *pos = value;
  GValue v = { 0, };
  GObject *target = NULL;
  GType value_type;

  /* do nothing if assignment is for missing element */
  if (element == NULL)
    goto out;

  /* parse the string, so the property name is null-terminated and pos points
     to the beginning of the value */
  while (!g_ascii_isspace (*pos) && (*pos != '=')) pos++;
  if (*pos == '=') {
    *pos = '\0';
  } else {
    *pos = '\0';
    pos++;
    while (g_ascii_isspace (*pos)) pos++;
  }
  pos++;
  while (g_ascii_isspace (*pos)) pos++;
  /* truncate a string if it is delimited with double quotes */
  if (*pos == '"' && pos[strlen (pos) - 1] == '"') {
    pos++;
    pos[strlen (pos) - 1] = '\0';
  }
  gst_parse_unescape (pos);

  if (GST_IS_CHILD_PROXY (element)) {
    if (!gst_child_proxy_lookup (GST_CHILD_PROXY (element), value, &target, &pspec)) {
      /* do a delayed set */
      gst_parse_add_delayed_set (element, value, pos);
    }
  } else {
    pspec = g_object_class_find_property (G_OBJECT_GET_CLASS (element), value);
    if (pspec != NULL) {
      target = G_OBJECT (g_object_ref (element));
      GST_CAT_LOG_OBJECT (GST_CAT_PIPELINE, target, "found %s property", value);
    } else {
      SET_ERROR (graph->error, GST_PARSE_ERROR_NO_SUCH_PROPERTY, \
          _("no property \"%s\" in element \"%s\""), value, \
          GST_ELEMENT_NAME (element));
    }
  }

  if (pspec != NULL && target != NULL) {
    gboolean got_value = FALSE;

    value_type = pspec->value_type;

    GST_CAT_LOG_OBJECT (GST_CAT_PIPELINE, element, "parsing property %s as a %s",
        pspec->name, g_type_name (value_type));

    g_value_init (&v, value_type);
    if (gst_value_deserialize (&v, pos))
      got_value = TRUE;
    else if (g_type_is_a (value_type, GST_TYPE_ELEMENT)) {
       GstElement *bin;

       bin = gst_parse_bin_from_description_full (pos, TRUE, NULL,
           GST_PARSE_FLAG_NO_SINGLE_ELEMENT_BINS | GST_PARSE_FLAG_PLACE_IN_BIN, NULL);
       if (bin) {
         g_value_set_object (&v, bin);
         got_value = TRUE;
       }
    }
    if (!got_value)
      goto error;
    g_object_set_property (target, pspec->name, &v);
  }

out:
  gst_parse_strfree (value);
  if (G_IS_VALUE (&v))
    g_value_unset (&v);
  if (target)
    gst_object_unref (target);
  return;

error:
  SET_ERROR (graph->error, GST_PARSE_ERROR_COULD_NOT_SET_PROPERTY,
         _("could not set property \"%s\" in element \"%s\" to \"%s\""),
	 value, GST_ELEMENT_NAME (element), pos);
  goto out;
}

static void gst_parse_element_preset (gchar *value, GstElement *element, graph_t *graph)
{
  /* do nothing if preset is for missing element or its not a preset element */
  if (element == NULL)
    goto out;

  if (!GST_IS_PRESET(element))
    goto not_a_preset;

  /* do nothing if no preset is given */
  if (value == NULL || *value == '\0')
    goto out;

  gst_parse_unescape (value);
  if (!gst_preset_load_preset (GST_PRESET (element), value))
    goto error;

out:
  gst_parse_strfree (value);
  return;

not_a_preset:
  SET_ERROR (graph->error, GST_PARSE_ERROR_COULD_NOT_SET_PROPERTY,
         _("Element \"%s\" is not a GstPreset"),
	 GST_ELEMENT_NAME (element));
  goto out;

error:
  SET_ERROR (graph->error, GST_PARSE_ERROR_COULD_NOT_SET_PROPERTY,
         _("could not set preset \"%s\" in element \"%s\""),
	 value, GST_ELEMENT_NAME (element));
  goto out;
}

static void gst_parse_free_reference (reference_t *rr)
{
  if(rr->element) gst_object_unref(rr->element);
  gst_parse_strfree (rr->name);
  g_slist_foreach (rr->pads, (GFunc) gst_parse_strfree, NULL);
  g_slist_free (rr->pads);
}

static void gst_parse_free_link (link_t *link)
{
  gst_parse_free_reference (&(link->src));
  gst_parse_free_reference (&(link->sink));
  if (link->caps) gst_caps_unref (link->caps);
  gst_parse_link_free (link);
}

static void gst_parse_free_chain (chain_t *ch)
{
  GSList *walk;
  gst_parse_free_reference (&(ch->first));
  gst_parse_free_reference (&(ch->last));
  for(walk=ch->elements;walk;walk=walk->next)
    gst_object_unref (walk->data);
  g_slist_free (ch->elements);
  gst_parse_chain_free (ch);
}

static void gst_parse_free_delayed_link (DelayedLink *link)
{
  g_free (link->src_pad);
  g_free (link->sink_pad);
  if (link->caps) gst_caps_unref (link->caps);
  g_slice_free (DelayedLink, link);
}

#define PRETTY_PAD_NAME_FMT "%s %s of %s named %s"
#define PRETTY_PAD_NAME_ARGS(elem, pad_name) \
  (pad_name ? "pad " : "some"), (pad_name ? pad_name : "pad"), \
  G_OBJECT_TYPE_NAME(elem), GST_STR_NULL (GST_ELEMENT_NAME (elem))

static void gst_parse_no_more_pads (GstElement *src, gpointer data)
{
  DelayedLink *link = data;

  /* Don't warn for all-pads links, as we expect those to
   * still be active at no-more-pads */
  if (!link->all_pads) {
    GST_ELEMENT_WARNING(src, PARSE, DELAYED_LINK,
      (_("Delayed linking failed.")),
      ("failed delayed linking " PRETTY_PAD_NAME_FMT " to " PRETTY_PAD_NAME_FMT,
          PRETTY_PAD_NAME_ARGS (src, link->src_pad),
          PRETTY_PAD_NAME_ARGS (link->sink, link->sink_pad)));
  }
  /* we keep the handlers connected, so that in case an element still adds a pad
   * despite no-more-pads, we will consider it for pending delayed links */
}

static void gst_parse_found_pad (GstElement *src, GstPad *pad, gpointer data)
{
  DelayedLink *link = data;

  GST_CAT_INFO (GST_CAT_PIPELINE,
                "trying delayed linking %s " PRETTY_PAD_NAME_FMT " to " PRETTY_PAD_NAME_FMT,
		            link->all_pads ? "all pads" : "one pad",
                PRETTY_PAD_NAME_ARGS (src, link->src_pad),
                PRETTY_PAD_NAME_ARGS (link->sink, link->sink_pad));

  if (gst_element_link_pads_filtered (src, link->src_pad, link->sink,
      link->sink_pad, link->caps)) {
    /* do this here, we don't want to get any problems later on when
     * unlocking states */
    GST_CAT_DEBUG (GST_CAT_PIPELINE,
                   "delayed linking %s " PRETTY_PAD_NAME_FMT " to " PRETTY_PAD_NAME_FMT " worked",
		               link->all_pads ? "all pads" : "one pad",
               	   PRETTY_PAD_NAME_ARGS (src, link->src_pad),
                   PRETTY_PAD_NAME_ARGS (link->sink, link->sink_pad));
    g_signal_handler_disconnect (src, link->no_more_pads_signal_id);
    /* releases 'link' */
    if (!link->all_pads)
      g_signal_handler_disconnect (src, link->pad_added_signal_id);
  }
}

/* both padnames and the caps may be NULL */
static gboolean
gst_parse_perform_delayed_link (GstElement *src, const gchar *src_pad,
                                GstElement *sink, const gchar *sink_pad,
                                GstCaps *caps, gboolean all_pads)
{
  GList *templs = gst_element_class_get_pad_template_list (
      GST_ELEMENT_GET_CLASS (src));

  for (; templs; templs = templs->next) {
    GstPadTemplate *templ = (GstPadTemplate *) templs->data;
    if ((GST_PAD_TEMPLATE_DIRECTION (templ) == GST_PAD_SRC) &&
        (GST_PAD_TEMPLATE_PRESENCE(templ) == GST_PAD_SOMETIMES))
    {
      DelayedLink *data = g_slice_new (DelayedLink);

      data->all_pads = all_pads;

      /* TODO: maybe we should check if src_pad matches this template's names */

      GST_CAT_DEBUG (GST_CAT_PIPELINE,
                     "trying delayed link " PRETTY_PAD_NAME_FMT " to " PRETTY_PAD_NAME_FMT,
                     PRETTY_PAD_NAME_ARGS (src, src_pad),
                     PRETTY_PAD_NAME_ARGS (sink, sink_pad));

      data->src_pad = g_strdup (src_pad);
      data->sink = sink;
      data->sink_pad = g_strdup (sink_pad);
      if (caps) {
      	data->caps = gst_caps_copy (caps);
      } else {
      	data->caps = NULL;
      }
      data->pad_added_signal_id = g_signal_connect_data (src, "pad-added",
          G_CALLBACK (gst_parse_found_pad), data,
          (GClosureNotify) gst_parse_free_delayed_link, (GConnectFlags) 0);
      data->no_more_pads_signal_id = g_signal_connect (src, "no-more-pads",
          G_CALLBACK (gst_parse_no_more_pads), data);
      return TRUE;
    }
  }
  return FALSE;
}

static gboolean
gst_parse_element_can_do_caps (GstElement * e, GstPadDirection dir,
    GstCaps * link_caps)
{
  gboolean can_do = FALSE, done = FALSE;
  GstIterator *it;

  it = (dir == GST_PAD_SRC) ? gst_element_iterate_src_pads (e) : gst_element_iterate_sink_pads (e);

  while (!done && !can_do) {
    GValue v = G_VALUE_INIT;
    GstPad *pad;
    GstCaps *caps;

    switch (gst_iterator_next (it, &v)) {
      case GST_ITERATOR_OK:
        pad = g_value_get_object (&v);

        caps = gst_pad_get_current_caps (pad);
        if (caps == NULL)
          caps = gst_pad_query_caps (pad, NULL);

        can_do = gst_caps_can_intersect (caps, link_caps);

        GST_TRACE ("can_do: %d for %" GST_PTR_FORMAT " and %" GST_PTR_FORMAT,
            can_do, caps, link_caps);

        gst_caps_unref (caps);

        g_value_unset (&v);
        break;
      case GST_ITERATOR_DONE:
      case GST_ITERATOR_ERROR:
        done = TRUE;
        break;
      case GST_ITERATOR_RESYNC:
        gst_iterator_resync (it);
        break;
    }
  }

  gst_iterator_free (it);

  return can_do;
}

/*
 * performs a link and frees the struct. src and sink elements must be given
 * return values   0 - link performed
 *                 1 - link delayed
 *                <0 - error
 */
static gint
gst_parse_perform_link (link_t *link, graph_t *graph)
{
  GstElement *src = link->src.element;
  GstElement *sink = link->sink.element;
  GSList *srcs = link->src.pads;
  GSList *sinks = link->sink.pads;
  g_assert (GST_IS_ELEMENT (src));
  g_assert (GST_IS_ELEMENT (sink));

  GST_CAT_INFO (GST_CAT_PIPELINE,
      "linking " PRETTY_PAD_NAME_FMT " to " PRETTY_PAD_NAME_FMT " (%u/%u) with caps \"%" GST_PTR_FORMAT "\"",
      PRETTY_PAD_NAME_ARGS (src, link->src.name),
      PRETTY_PAD_NAME_ARGS (sink, link->sink.name),
      g_slist_length (srcs), g_slist_length (sinks), link->caps);

  if (!srcs || !sinks) {
    gboolean found_one = gst_element_link_pads_filtered (src,
        srcs ? (const gchar *) srcs->data : NULL, sink,
        sinks ? (const gchar *) sinks->data : NULL, link->caps);

    if (found_one) {
      if (!link->all_pads)
        goto success; /* Linked one, and not an all-pads link = we're done */

      /* Try and link more available pads */
      while (gst_element_link_pads_filtered (src,
        srcs ? (const gchar *) srcs->data : NULL, sink,
        sinks ? (const gchar *) sinks->data : NULL, link->caps));
    }

    /* We either didn't find any static pads, or this is a all-pads link,
     * in which case watch for future pads and link those. Not a failure
     * in the all-pads case if there's no sometimes pads to watch */
    if (gst_parse_perform_delayed_link (src,
          srcs ? (const gchar *) srcs->data : NULL,
          sink, sinks ? (const gchar *) sinks->data : NULL, link->caps,
	  link->all_pads) || link->all_pads) {
      goto success;
    } else {
      goto error;
    }
  }
  if (g_slist_length (link->src.pads) != g_slist_length (link->sink.pads)) {
    goto error;
  }
  while (srcs && sinks) {
    const gchar *src_pad = (const gchar *) srcs->data;
    const gchar *sink_pad = (const gchar *) sinks->data;
    srcs = g_slist_next (srcs);
    sinks = g_slist_next (sinks);
    if (gst_element_link_pads_filtered (src, src_pad, sink, sink_pad,
        link->caps)) {
      continue;
    } else {
      if (gst_parse_perform_delayed_link (src, src_pad,
                                          sink, sink_pad,
					  link->caps, link->all_pads)) {
	continue;
      } else {
        goto error;
      }
    }
  }

success:
  gst_parse_free_link (link);
  return 0;

error:
  if (link->caps != NULL) {
    gboolean src_can_do_caps, sink_can_do_caps;
    gchar *caps_str = gst_caps_to_string (link->caps);

    src_can_do_caps =
        gst_parse_element_can_do_caps (src, GST_PAD_SRC, link->caps);
    sink_can_do_caps =
        gst_parse_element_can_do_caps (sink, GST_PAD_SINK, link->caps);

    if (!src_can_do_caps && sink_can_do_caps) {
      SET_ERROR (graph->error, GST_PARSE_ERROR_LINK,
          _("could not link %s to %s, %s can't handle caps %s"),
          GST_ELEMENT_NAME (src), GST_ELEMENT_NAME (sink),
          GST_ELEMENT_NAME (src), caps_str);
    } else if (src_can_do_caps && !sink_can_do_caps) {
      SET_ERROR (graph->error, GST_PARSE_ERROR_LINK,
          _("could not link %s to %s, %s can't handle caps %s"),
          GST_ELEMENT_NAME (src), GST_ELEMENT_NAME (sink),
          GST_ELEMENT_NAME (sink), caps_str);
    } else if (!src_can_do_caps && !sink_can_do_caps) {
      SET_ERROR (graph->error, GST_PARSE_ERROR_LINK,
          _("could not link %s to %s, neither element can handle caps %s"),
          GST_ELEMENT_NAME (src), GST_ELEMENT_NAME (sink), caps_str);
    } else {
      SET_ERROR (graph->error, GST_PARSE_ERROR_LINK,
          _("could not link %s to %s with caps %s"),
          GST_ELEMENT_NAME (src), GST_ELEMENT_NAME (sink), caps_str);
    }
    g_free (caps_str);
  } else {
    SET_ERROR (graph->error, GST_PARSE_ERROR_LINK,
        _("could not link %s to %s"), GST_ELEMENT_NAME (src),
        GST_ELEMENT_NAME (sink));
  }
  gst_parse_free_link (link);
  return -1;
}


static int yyerror (void *scanner, graph_t *graph, const char *s);

#line 859 "gst/parse/grammar.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "grammar.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PARSE_URL = 3,                  /* PARSE_URL  */
  YYSYMBOL_IDENTIFIER = 4,                 /* IDENTIFIER  */
  YYSYMBOL_REF = 5,                        /* REF  */
  YYSYMBOL_PADREF = 6,                     /* PADREF  */
  YYSYMBOL_BINREF = 7,                     /* BINREF  */
  YYSYMBOL_ASSIGNMENT = 8,                 /* ASSIGNMENT  */
  YYSYMBOL_PRESET = 9,                     /* PRESET  */
  YYSYMBOL_LINK = 10,                      /* LINK  */
  YYSYMBOL_LINK_ALL = 11,                  /* LINK_ALL  */
  YYSYMBOL_12_ = 12,                       /* '('  */
  YYSYMBOL_13_ = 13,                       /* ')'  */
  YYSYMBOL_14_ = 14,                       /* ','  */
  YYSYMBOL_15_ = 15,                       /* '.'  */
  YYSYMBOL_16_ = 16,                       /* '!'  */
  YYSYMBOL_17_ = 17,                       /* '='  */
  YYSYMBOL_18_ = 18,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 19,                  /* $accept  */
  YYSYMBOL_element = 20,                   /* element  */
  YYSYMBOL_elementary = 21,                /* elementary  */
  YYSYMBOL_chain = 22,                     /* chain  */
  YYSYMBOL_openchain = 23,                 /* openchain  */
  YYSYMBOL_link = 24,                      /* link  */
  YYSYMBOL_pads = 25,                      /* pads  */
  YYSYMBOL_morepads = 26,                  /* morepads  */
  YYSYMBOL_reference = 27,                 /* reference  */
  YYSYMBOL_chainlist = 28,                 /* chainlist  */
  YYSYMBOL_assignments = 29,               /* assignments  */
  YYSYMBOL_binopener = 30,                 /* binopener  */
  YYSYMBOL_bin = 31,                       /* bin  */
  YYSYMBOL_graph = 32                      /* graph  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   36

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  19
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  29
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  39

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   266


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    16,     2,     2,     2,     2,     2,     2,
      12,    13,     2,     2,    14,     2,    15,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    18,     2,
       2,    17,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   847,   847,   854,   857,   872,   880,   911,   929,   933,
     947,   956,   966,   967,   971,   972,   984,  1003,  1035,  1047,
    1055,  1086,  1087,  1096,  1108,  1109,  1112,  1113,  1115,  1159
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PARSE_URL",
  "IDENTIFIER", "REF", "PADREF", "BINREF", "ASSIGNMENT", "PRESET", "LINK",
  "LINK_ALL", "'('", "')'", "','", "'.'", "'!'", "'='", "':'", "$accept",
  "element", "elementary", "chain", "openchain", "link", "pads",
  "morepads", "reference", "chainlist", "assignments", "binopener", "bin",
  "graph", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,    40,    41,    44,    46,    33,    61,    58
};
#endif

#define YYPACT_NINF (-20)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-30)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -20,     0,     6,   -20,   -20,   -20,    -4,   -20,   -20,    21,
      18,   -20,    23,   -20,     8,   -20,   -20,    16,   -20,   -20,
     -20,    -4,   -20,   -20,   -20,    22,     8,   -20,    -4,   -20,
     -20,    14,   -20,   -20,    10,   -20,    18,   -20,   -20
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      21,     0,     0,    23,    17,     2,    14,    27,    26,     5,
      12,    22,     7,    19,    24,     6,     1,     0,    20,     4,
       3,    14,     8,    10,    11,    12,    24,    21,    14,    13,
      16,     0,    18,    25,     0,    15,    12,    28,     9
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -20,   -20,     1,   -20,   -20,   -20,   -17,   -19,    11,     4,
       9,   -20,   -20,   -20
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     9,    10,    11,    12,    25,    22,    18,    13,     1,
      27,    14,    15,     2
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
     -29,     3,    29,     4,     5,     6,    16,     7,    31,    35,
      17,     3,     8,     4,     5,     6,    26,     7,     5,    38,
      28,     7,     8,    37,    21,    30,     8,     6,    21,    19,
      20,    34,    36,    23,    24,    33,    32
};

static const yytype_int8 yycheck[] =
{
       0,     1,    21,     3,     4,     5,     0,     7,    25,    28,
      14,     1,    12,     3,     4,     5,     8,     7,     4,    36,
       4,     7,    12,    13,     6,     3,    12,     5,     6,     8,
       9,    27,    31,    10,    11,    26,    25
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    28,    32,     1,     3,     4,     5,     7,    12,    20,
      21,    22,    23,    27,    30,    31,     0,    14,    26,     8,
       9,     6,    25,    10,    11,    24,     8,    29,     4,    26,
       3,    25,    27,    29,    28,    26,    21,    13,    25
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    19,    20,    20,    20,    21,    21,    22,    23,    23,
      24,    24,    25,    25,    26,    26,    22,    23,    22,    23,
      27,    28,    28,    28,    29,    29,    30,    30,    31,    32
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     1,     2,     5,
       1,     1,     0,     2,     0,     3,     3,     1,     3,     1,
       2,     0,     2,     2,     0,     2,     1,     1,     4,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, graph, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner, graph); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner, graph_t *graph)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  YYUSE (graph);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner, graph_t *graph)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner, graph);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner, graph_t *graph)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner, graph);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner, graph); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner, graph_t *graph)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  YYUSE (graph);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_PARSE_URL: /* PARSE_URL  */
#line 812 "gst/parse/grammar.y"
            {	gst_parse_strfree (((*yyvaluep).ss));		}
#line 1634 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_IDENTIFIER: /* IDENTIFIER  */
#line 812 "gst/parse/grammar.y"
            {	gst_parse_strfree (((*yyvaluep).ss));		}
#line 1640 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_REF: /* REF  */
#line 812 "gst/parse/grammar.y"
            {	gst_parse_strfree (((*yyvaluep).ss));		}
#line 1646 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_PADREF: /* PADREF  */
#line 812 "gst/parse/grammar.y"
            {	gst_parse_strfree (((*yyvaluep).ss));		}
#line 1652 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_BINREF: /* BINREF  */
#line 812 "gst/parse/grammar.y"
            {	gst_parse_strfree (((*yyvaluep).ss));		}
#line 1658 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_ASSIGNMENT: /* ASSIGNMENT  */
#line 812 "gst/parse/grammar.y"
            {	gst_parse_strfree (((*yyvaluep).ss));		}
#line 1664 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_PRESET: /* PRESET  */
#line 812 "gst/parse/grammar.y"
            {	gst_parse_strfree (((*yyvaluep).ss));		}
#line 1670 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_LINK: /* LINK  */
#line 812 "gst/parse/grammar.y"
            {	gst_parse_strfree (((*yyvaluep).ss));		}
#line 1676 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_LINK_ALL: /* LINK_ALL  */
#line 812 "gst/parse/grammar.y"
            {	gst_parse_strfree (((*yyvaluep).ss));		}
#line 1682 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_element: /* element  */
#line 817 "gst/parse/grammar.y"
            {	gst_object_unref (((*yyvaluep).ee));		}
#line 1688 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_elementary: /* elementary  */
#line 813 "gst/parse/grammar.y"
            {	if(((*yyvaluep).cc))
		  gst_parse_free_chain(((*yyvaluep).cc));	}
#line 1695 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_chain: /* chain  */
#line 813 "gst/parse/grammar.y"
            {	if(((*yyvaluep).cc))
		  gst_parse_free_chain(((*yyvaluep).cc));	}
#line 1702 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_openchain: /* openchain  */
#line 813 "gst/parse/grammar.y"
            {	if(((*yyvaluep).cc))
		  gst_parse_free_chain(((*yyvaluep).cc));	}
#line 1709 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_link: /* link  */
#line 815 "gst/parse/grammar.y"
            {	gst_parse_free_link (((*yyvaluep).ll));	}
#line 1715 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_pads: /* pads  */
#line 818 "gst/parse/grammar.y"
            {	GSList *walk;
		for(walk=((*yyvaluep).pp);walk;walk=walk->next)
		  gst_parse_strfree (walk->data);
		g_slist_free (((*yyvaluep).pp));		}
#line 1724 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_morepads: /* morepads  */
#line 818 "gst/parse/grammar.y"
            {	GSList *walk;
		for(walk=((*yyvaluep).pp);walk;walk=walk->next)
		  gst_parse_strfree (walk->data);
		g_slist_free (((*yyvaluep).pp));		}
#line 1733 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_reference: /* reference  */
#line 816 "gst/parse/grammar.y"
            {	gst_parse_free_reference(&(((*yyvaluep).rr)));}
#line 1739 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_chainlist: /* chainlist  */
#line 813 "gst/parse/grammar.y"
            {	if(((*yyvaluep).cc))
		  gst_parse_free_chain(((*yyvaluep).cc));	}
#line 1746 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_assignments: /* assignments  */
#line 818 "gst/parse/grammar.y"
            {	GSList *walk;
		for(walk=((*yyvaluep).pp);walk;walk=walk->next)
		  gst_parse_strfree (walk->data);
		g_slist_free (((*yyvaluep).pp));		}
#line 1755 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_binopener: /* binopener  */
#line 812 "gst/parse/grammar.y"
            {	gst_parse_strfree (((*yyvaluep).ss));		}
#line 1761 "gst/parse/grammar.tab.c"
        break;

    case YYSYMBOL_bin: /* bin  */
#line 813 "gst/parse/grammar.y"
            {	if(((*yyvaluep).cc))
		  gst_parse_free_chain(((*yyvaluep).cc));	}
#line 1768 "gst/parse/grammar.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner, graph_t *graph)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* element: IDENTIFIER  */
#line 847 "gst/parse/grammar.y"
                                              { (yyval.ee) = gst_element_factory_make ((yyvsp[0].ss), NULL);
						if ((yyval.ee) == NULL) {
						  add_missing_element(graph, (yyvsp[0].ss));
						  SET_ERROR (graph->error, GST_PARSE_ERROR_NO_SUCH_ELEMENT, _("no element \"%s\""), (yyvsp[0].ss));
						}
						gst_parse_strfree ((yyvsp[0].ss));
                                              }
#line 2048 "gst/parse/grammar.tab.c"
    break;

  case 3: /* element: element PRESET  */
#line 854 "gst/parse/grammar.y"
                                          { gst_parse_element_preset ((yyvsp[0].ss), (yyvsp[-1].ee), graph);
						(yyval.ee) = (yyvsp[-1].ee);
	                                      }
#line 2056 "gst/parse/grammar.tab.c"
    break;

  case 4: /* element: element ASSIGNMENT  */
#line 857 "gst/parse/grammar.y"
                                              { gst_parse_element_set ((yyvsp[0].ss), (yyvsp[-1].ee), graph);
						(yyval.ee) = (yyvsp[-1].ee);
	                                      }
#line 2064 "gst/parse/grammar.tab.c"
    break;

  case 5: /* elementary: element  */
#line 872 "gst/parse/grammar.y"
                                              { (yyval.cc) = gst_parse_chain_new ();
						/* g_print ("@%p: CHAINing elementary\n", $$); */
						(yyval.cc)->first.element = (yyvsp[0].ee)? gst_object_ref((yyvsp[0].ee)) : NULL;
						(yyval.cc)->last.element = (yyvsp[0].ee)? gst_object_ref((yyvsp[0].ee)) : NULL;
						(yyval.cc)->first.name = (yyval.cc)->last.name = NULL;
						(yyval.cc)->first.pads = (yyval.cc)->last.pads = NULL;
						(yyval.cc)->elements = (yyvsp[0].ee) ? g_slist_prepend (NULL, (yyvsp[0].ee)) : NULL;
					      }
#line 2077 "gst/parse/grammar.tab.c"
    break;

  case 6: /* elementary: bin  */
#line 880 "gst/parse/grammar.y"
                                              { (yyval.cc)=(yyvsp[0].cc); }
#line 2083 "gst/parse/grammar.tab.c"
    break;

  case 7: /* chain: openchain  */
#line 911 "gst/parse/grammar.y"
                                              { (yyval.cc)=(yyvsp[0].cc);
						if((yyval.cc)->last.name){
							SET_ERROR (graph->error, GST_PARSE_ERROR_SYNTAX,
							_("unexpected reference \"%s\" - ignoring"), (yyval.cc)->last.name);
							gst_parse_strfree((yyval.cc)->last.name);
							(yyval.cc)->last.name=NULL;
						}
						if((yyval.cc)->last.pads){
							SET_ERROR (graph->error, GST_PARSE_ERROR_SYNTAX,
							_("unexpected pad-reference \"%s\" - ignoring"), (gchar*)(yyval.cc)->last.pads->data);
							g_slist_foreach ((yyval.cc)->last.pads, (GFunc) gst_parse_strfree, NULL);
							g_slist_free ((yyval.cc)->last.pads);
							(yyval.cc)->last.pads=NULL;
						}
					      }
#line 2103 "gst/parse/grammar.tab.c"
    break;

  case 8: /* openchain: elementary pads  */
#line 929 "gst/parse/grammar.y"
                                              { (yyval.cc)=(yyvsp[-1].cc);
						(yyval.cc)->last.pads = g_slist_concat ((yyval.cc)->last.pads, (yyvsp[0].pp));
						/* g_print ("@%p@%p: FKI elementary pads\n", $1, $$->last.pads); */
					      }
#line 2112 "gst/parse/grammar.tab.c"
    break;

  case 9: /* openchain: openchain link pads elementary pads  */
#line 934 "gst/parse/grammar.y"
                                              {
						(yyvsp[-3].ll)->src  = (yyvsp[-4].cc)->last;
						(yyvsp[-3].ll)->sink = (yyvsp[-1].cc)->first;
						(yyvsp[-3].ll)->sink.pads = g_slist_concat ((yyvsp[-2].pp), (yyvsp[-3].ll)->sink.pads);
						TRY_SETUP_LINK((yyvsp[-3].ll));
						(yyvsp[-1].cc)->first = (yyvsp[-4].cc)->first;
						(yyvsp[-1].cc)->elements = g_slist_concat ((yyvsp[-4].cc)->elements, (yyvsp[-1].cc)->elements);
						gst_parse_chain_free((yyvsp[-4].cc));
						(yyval.cc) = (yyvsp[-1].cc);
						(yyval.cc)->last.pads = g_slist_concat ((yyval.cc)->last.pads, (yyvsp[0].pp));
					      }
#line 2128 "gst/parse/grammar.tab.c"
    break;

  case 10: /* link: LINK  */
#line 947 "gst/parse/grammar.y"
                                              { (yyval.ll) = gst_parse_link_new ();
						(yyval.ll)->all_pads = FALSE;
						if ((yyvsp[0].ss)) {
						  (yyval.ll)->caps = gst_caps_from_string ((yyvsp[0].ss));
						  if ((yyval.ll)->caps == NULL)
						    SET_ERROR (graph->error, GST_PARSE_ERROR_LINK, _("could not parse caps \"%s\""), (yyvsp[0].ss));
						  gst_parse_strfree ((yyvsp[0].ss));
						}
					      }
#line 2142 "gst/parse/grammar.tab.c"
    break;

  case 11: /* link: LINK_ALL  */
#line 956 "gst/parse/grammar.y"
                                              { (yyval.ll) = gst_parse_link_new ();
						(yyval.ll)->all_pads = TRUE;
						if ((yyvsp[0].ss)) {
						  (yyval.ll)->caps = gst_caps_from_string ((yyvsp[0].ss));
						  if ((yyval.ll)->caps == NULL)
						    SET_ERROR (graph->error, GST_PARSE_ERROR_LINK, _("could not parse caps \"%s\""), (yyvsp[0].ss));
						  gst_parse_strfree ((yyvsp[0].ss));
						}
					      }
#line 2156 "gst/parse/grammar.tab.c"
    break;

  case 12: /* pads: %empty  */
#line 966 "gst/parse/grammar.y"
                                              { (yyval.pp) = NULL; }
#line 2162 "gst/parse/grammar.tab.c"
    break;

  case 13: /* pads: PADREF morepads  */
#line 967 "gst/parse/grammar.y"
                                              { (yyval.pp) = (yyvsp[0].pp);
						(yyval.pp) = g_slist_prepend ((yyval.pp), (yyvsp[-1].ss));
					      }
#line 2170 "gst/parse/grammar.tab.c"
    break;

  case 14: /* morepads: %empty  */
#line 971 "gst/parse/grammar.y"
                                              { (yyval.pp) = NULL; }
#line 2176 "gst/parse/grammar.tab.c"
    break;

  case 15: /* morepads: ',' IDENTIFIER morepads  */
#line 972 "gst/parse/grammar.y"
                                              { (yyval.pp) = g_slist_prepend ((yyvsp[0].pp), (yyvsp[-1].ss)); }
#line 2182 "gst/parse/grammar.tab.c"
    break;

  case 16: /* chain: openchain link PARSE_URL  */
#line 984 "gst/parse/grammar.y"
                                              { GstElement *element =
							  gst_element_make_from_uri (GST_URI_SINK, (yyvsp[0].ss), NULL, NULL);
						/* FIXME: get and parse error properly */
						if (!element) {
						  SET_ERROR (graph->error, GST_PARSE_ERROR_NO_SUCH_ELEMENT,
							  _("no sink element for URI \"%s\""), (yyvsp[0].ss));
						}
						(yyval.cc) = (yyvsp[-2].cc);
						(yyvsp[-1].ll)->sink.element = element?gst_object_ref(element):NULL;
						(yyvsp[-1].ll)->src = (yyvsp[-2].cc)->last;
						TRY_SETUP_LINK((yyvsp[-1].ll));
						(yyval.cc)->last.element = NULL;
						(yyval.cc)->last.name = NULL;
						(yyval.cc)->last.pads = NULL;
						if(element) (yyval.cc)->elements = g_slist_append ((yyval.cc)->elements, element);
						g_free ((yyvsp[0].ss));
					      }
#line 2204 "gst/parse/grammar.tab.c"
    break;

  case 17: /* openchain: PARSE_URL  */
#line 1003 "gst/parse/grammar.y"
                                              { GstElement *element =
							  gst_element_make_from_uri (GST_URI_SRC, (yyvsp[0].ss), NULL, NULL);
						/* FIXME: get and parse error properly */
						if (!element) {
						  SET_ERROR (graph->error, GST_PARSE_ERROR_NO_SUCH_ELEMENT,
						    _("no source element for URI \"%s\""), (yyvsp[0].ss));
						}
						(yyval.cc) = gst_parse_chain_new ();
						/* g_print ("@%p: CHAINing srcURL\n", $$); */
						(yyval.cc)->first.element = NULL;
						(yyval.cc)->first.name = NULL;
						(yyval.cc)->first.pads = NULL;
						(yyval.cc)->last.element = element ? gst_object_ref(element):NULL;
						(yyval.cc)->last.name = NULL;
						(yyval.cc)->last.pads = NULL;
						(yyval.cc)->elements = element ? g_slist_prepend (NULL, element)  : NULL;
						g_free((yyvsp[0].ss));
					      }
#line 2227 "gst/parse/grammar.tab.c"
    break;

  case 18: /* chain: openchain link reference  */
#line 1035 "gst/parse/grammar.y"
                                              { (yyval.cc) = (yyvsp[-2].cc);
						(yyvsp[-1].ll)->sink= (yyvsp[0].rr);
						(yyvsp[-1].ll)->src = (yyvsp[-2].cc)->last;
						TRY_SETUP_LINK((yyvsp[-1].ll));
						(yyval.cc)->last.element = NULL;
						(yyval.cc)->last.name = NULL;
						(yyval.cc)->last.pads = NULL;
					      }
#line 2240 "gst/parse/grammar.tab.c"
    break;

  case 19: /* openchain: reference  */
#line 1047 "gst/parse/grammar.y"
                                              { (yyval.cc) = gst_parse_chain_new ();
						(yyval.cc)->last=(yyvsp[0].rr);
						(yyval.cc)->first.element = NULL;
						(yyval.cc)->first.name = NULL;
						(yyval.cc)->first.pads = NULL;
						(yyval.cc)->elements = NULL;
					      }
#line 2252 "gst/parse/grammar.tab.c"
    break;

  case 20: /* reference: REF morepads  */
#line 1055 "gst/parse/grammar.y"
                                              {
						gchar *padname = (yyvsp[-1].ss);
						GSList *pads = (yyvsp[0].pp);
						if (padname) {
						  while (*padname != '.') padname++;
						  *padname = '\0';
						  padname++;
						  if (*padname != '\0')
						    pads = g_slist_prepend (pads, gst_parse_strdup (padname));
						}
						(yyval.rr).element=NULL;
						(yyval.rr).name=(yyvsp[-1].ss);
						(yyval.rr).pads=pads;
					      }
#line 2271 "gst/parse/grammar.tab.c"
    break;

  case 21: /* chainlist: %empty  */
#line 1086 "gst/parse/grammar.y"
                                              { (yyval.cc) = NULL; }
#line 2277 "gst/parse/grammar.tab.c"
    break;

  case 22: /* chainlist: chainlist chain  */
#line 1087 "gst/parse/grammar.y"
                                              { if ((yyvsp[-1].cc)){
						  gst_parse_free_reference(&((yyvsp[-1].cc)->last));
						  gst_parse_free_reference(&((yyvsp[0].cc)->first));
						  (yyvsp[0].cc)->first = (yyvsp[-1].cc)->first;
						  (yyvsp[0].cc)->elements = g_slist_concat ((yyvsp[-1].cc)->elements, (yyvsp[0].cc)->elements);
						  gst_parse_chain_free ((yyvsp[-1].cc));
						}
						(yyval.cc) = (yyvsp[0].cc);
					      }
#line 2291 "gst/parse/grammar.tab.c"
    break;

  case 23: /* chainlist: chainlist error  */
#line 1096 "gst/parse/grammar.y"
                                              { (yyval.cc)=(yyvsp[-1].cc);
						GST_CAT_DEBUG (GST_CAT_PIPELINE,"trying to recover from syntax error");
						SET_ERROR (graph->error, GST_PARSE_ERROR_SYNTAX, _("syntax error"));
					      }
#line 2300 "gst/parse/grammar.tab.c"
    break;

  case 24: /* assignments: %empty  */
#line 1108 "gst/parse/grammar.y"
                                              { (yyval.pp) = NULL; }
#line 2306 "gst/parse/grammar.tab.c"
    break;

  case 25: /* assignments: ASSIGNMENT assignments  */
#line 1109 "gst/parse/grammar.y"
                                              { (yyval.pp) = g_slist_prepend ((yyvsp[0].pp), (yyvsp[-1].ss)); }
#line 2312 "gst/parse/grammar.tab.c"
    break;

  case 26: /* binopener: '('  */
#line 1112 "gst/parse/grammar.y"
                                              { (yyval.ss) = gst_parse_strdup("bin"); }
#line 2318 "gst/parse/grammar.tab.c"
    break;

  case 27: /* binopener: BINREF  */
#line 1113 "gst/parse/grammar.y"
                                              { (yyval.ss) = (yyvsp[0].ss); }
#line 2324 "gst/parse/grammar.tab.c"
    break;

  case 28: /* bin: binopener assignments chainlist ')'  */
#line 1115 "gst/parse/grammar.y"
                                              {
						chain_t *chain = (yyvsp[-1].cc);
						GSList *walk;
						GstBin *bin = (GstBin *) gst_element_factory_make ((yyvsp[-3].ss), NULL);
						if (!chain) {
						  SET_ERROR (graph->error, GST_PARSE_ERROR_EMPTY_BIN,
						    _("specified empty bin \"%s\", not allowed"), (yyvsp[-3].ss));
						  chain = gst_parse_chain_new ();
						  chain->first.element = chain->last.element = NULL;
						  chain->first.name    = chain->last.name    = NULL;
						  chain->first.pads    = chain->last.pads    = NULL;
						  chain->elements = NULL;
						}
						if (!bin) {
						  add_missing_element(graph, (yyvsp[-3].ss));
						  SET_ERROR (graph->error, GST_PARSE_ERROR_NO_SUCH_ELEMENT,
						    _("no bin \"%s\", unpacking elements"), (yyvsp[-3].ss));
						  /* clear property-list */
						  g_slist_foreach ((yyvsp[-2].pp), (GFunc) gst_parse_strfree, NULL);
						  g_slist_free ((yyvsp[-2].pp));
						  (yyvsp[-2].pp) = NULL;
						} else {
						  for (walk = chain->elements; walk; walk = walk->next )
						    gst_bin_add (bin, GST_ELEMENT (walk->data));
						  g_slist_free (chain->elements);
						  chain->elements = g_slist_prepend (NULL, bin);
						}
						(yyval.cc) = chain;
						/* set the properties now
						 * HINT: property-list cleared above, if bin==NULL
						 */
						for (walk = (yyvsp[-2].pp); walk; walk = walk->next)
						  gst_parse_element_set ((gchar *) walk->data,
							GST_ELEMENT (bin), graph);
						g_slist_free ((yyvsp[-2].pp));
						gst_parse_strfree ((yyvsp[-3].ss));
					      }
#line 2366 "gst/parse/grammar.tab.c"
    break;

  case 29: /* graph: chainlist  */
#line 1159 "gst/parse/grammar.y"
                                              { (yyval.gg) = graph;
						(yyval.gg)->chain = (yyvsp[0].cc);
						if(!(yyvsp[0].cc)) {
						  SET_ERROR (graph->error, GST_PARSE_ERROR_EMPTY, _("empty pipeline not allowed"));
						}
					      }
#line 2377 "gst/parse/grammar.tab.c"
    break;


#line 2381 "gst/parse/grammar.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, graph, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner, graph);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner, graph);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, graph, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner, graph);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner, graph);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1167 "gst/parse/grammar.y"



static int
yyerror (void *scanner, graph_t *graph, const char *s)
{
  /* FIXME: This should go into the GError somehow, but how? */
  GST_WARNING ("Error during parsing: %s", s);
  return -1;
}


GstElement *
priv_gst_parse_launch (const gchar *str, GError **error, GstParseContext *ctx,
    GstParseFlags flags)
{
  graph_t g;
  gchar *dstr;
  GSList *walk;
  GstElement *ret;
  yyscan_t scanner;

  g_return_val_if_fail (str != NULL, NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  g.chain = NULL;
  g.links = NULL;
  g.error = error;
  g.ctx = ctx;
  g.flags = flags;

#ifdef __GST_PARSE_TRACE
  GST_CAT_DEBUG (GST_CAT_PIPELINE, "TRACE: tracing enabled");
  __strings = __chains = __links = 0;
#endif /* __GST_PARSE_TRACE */

  /* g_print("Now scanning: %s\n", str); */

  dstr = g_strdup (str);
  priv_gst_parse_yylex_init (&scanner);
  priv_gst_parse_yy_scan_string (dstr, scanner);

#if YYDEBUG
  yydebug = 1;
#endif

  if (yyparse (scanner, &g) != 0) {
    SET_ERROR (error, GST_PARSE_ERROR_SYNTAX,
        "Unrecoverable syntax error while parsing pipeline %s", str);

    priv_gst_parse_yylex_destroy (scanner);
    g_free (dstr);

    goto error1;
  }
  priv_gst_parse_yylex_destroy (scanner);
  g_free (dstr);

  GST_CAT_DEBUG (GST_CAT_PIPELINE, "got %u elements and %u links",
      g.chain ? g_slist_length (g.chain->elements) : 0,
      g_slist_length (g.links));

  /* ensure chain is not NULL */
  if (!g.chain){
    g.chain=gst_parse_chain_new ();
    g.chain->elements=NULL;
    g.chain->first.element=NULL;
    g.chain->first.name=NULL;
    g.chain->first.pads=NULL;
    g.chain->last.element=NULL;
    g.chain->last.name=NULL;
    g.chain->last.pads=NULL;
  };

  /* ensure elements is not empty */
  if(!g.chain->elements){
    g.chain->elements= g_slist_prepend (NULL, NULL);
  };

  /* put all elements in our bin if necessary */
  if(g.chain->elements->next){
    GstBin *bin;
    if (flags & GST_PARSE_FLAG_PLACE_IN_BIN)
      bin = GST_BIN (gst_element_factory_make ("bin", NULL));
    else
      bin = GST_BIN (gst_element_factory_make ("pipeline", NULL));
    g_assert (bin);

    for (walk = g.chain->elements; walk; walk = walk->next) {
      if (walk->data != NULL)
        gst_bin_add (bin, GST_ELEMENT (walk->data));
    }
    g_slist_free (g.chain->elements);
    g.chain->elements = g_slist_prepend (NULL, bin);
  }

  ret = (GstElement *) g.chain->elements->data;
  g_slist_free (g.chain->elements);
  g.chain->elements=NULL;
  gst_parse_free_chain (g.chain);
  g.chain = NULL;


  /* resolve and perform links */
  for (walk = g.links; walk; walk = walk->next) {
    link_t *l = (link_t *) walk->data;
    int err;
    err=gst_resolve_reference( &(l->src), ret);
    if (err) {
       if(-1==err){
          SET_ERROR (error, GST_PARSE_ERROR_NO_SUCH_ELEMENT,
              "No src-element named \"%s\" - omitting link", l->src.name);
       }else{
          /* probably a missing element which we've handled already */
          SET_ERROR (error, GST_PARSE_ERROR_NO_SUCH_ELEMENT,
              "No src-element found - omitting link");
       }
       gst_parse_free_link (l);
       continue;
    }

    err=gst_resolve_reference( &(l->sink), ret);
    if (err) {
       if(-1==err){
          SET_ERROR (error, GST_PARSE_ERROR_NO_SUCH_ELEMENT,
              "No sink-element named \"%s\" - omitting link", l->src.name);
       }else{
          /* probably a missing element which we've handled already */
          SET_ERROR (error, GST_PARSE_ERROR_NO_SUCH_ELEMENT,
              "No sink-element found - omitting link");
       }
       gst_parse_free_link (l);
       continue;
    }
    gst_parse_perform_link (l, &g);
  }
  g_slist_free (g.links);

out:
#ifdef __GST_PARSE_TRACE
  GST_CAT_DEBUG (GST_CAT_PIPELINE,
      "TRACE: %u strings, %u chains and %u links left", __strings, __chains,
      __links);
  if (__strings || __chains || __links) {
    g_warning ("TRACE: %u strings, %u chains and %u links left", __strings,
        __chains, __links);
  }
#endif /* __GST_PARSE_TRACE */

  return ret;

error1:
  if (g.chain) {
    gst_parse_free_chain (g.chain);
    g.chain=NULL;
  }

  g_slist_foreach (g.links, (GFunc)gst_parse_free_link, NULL);
  g_slist_free (g.links);

  if (error)
    g_assert (*error);
  ret = NULL;

  goto out;
}
