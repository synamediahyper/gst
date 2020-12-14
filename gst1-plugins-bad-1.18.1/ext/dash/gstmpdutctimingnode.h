/* GStreamer
 *
 * Copyright (C) 2019 Collabora Ltd.
 *   Author: Stéphane Cerveau <scerveau@collabora.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library (COPYING); if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#ifndef __GSTMPDUTCTIMINGNODE_H__
#define __GSTMPDUTCTIMINGNODE_H__

#include <gst/gst.h>
#include "gstmpdnode.h"

G_BEGIN_DECLS

#define GST_TYPE_MPD_UTCTIMING_NODE gst_mpd_utctiming_node_get_type ()
G_DECLARE_FINAL_TYPE (GstMPDUTCTimingNode, gst_mpd_utctiming_node, GST, MPD_UTCTIMING_NODE, GstMPDNode)

typedef enum
{
  GST_MPD_UTCTIMING_TYPE_UNKNOWN     = 0x00,
  GST_MPD_UTCTIMING_TYPE_NTP         = 0x01,
  GST_MPD_UTCTIMING_TYPE_SNTP        = 0x02,
  GST_MPD_UTCTIMING_TYPE_HTTP_HEAD   = 0x04,
  GST_MPD_UTCTIMING_TYPE_HTTP_XSDATE = 0x08,
  GST_MPD_UTCTIMING_TYPE_HTTP_ISO    = 0x10,
  GST_MPD_UTCTIMING_TYPE_HTTP_NTP    = 0x20,
  GST_MPD_UTCTIMING_TYPE_DIRECT      = 0x40
} GstMPDUTCTimingType;

struct GstMPDUTCTimingMethod
{
  const gchar *name;
  GstMPDUTCTimingType method;
};

struct _GstMPDUTCTimingNode
{
  GstObject parent_instance;
  GstMPDUTCTimingType method;
  /* NULL terminated array of strings */
  gchar **urls;
  /* TODO add missing fields such as weight etc.*/
};


GstMPDUTCTimingNode * gst_mpd_utctiming_node_new (void);
void gst_mpd_utctiming_node_free (GstMPDUTCTimingNode* self);

const gchar* gst_mpd_utctiming_get_scheme_id_uri (GstMPDUTCTimingType type);
GstMPDUTCTimingType gst_mpd_utctiming_get_method (gchar* schemeIDURI);

G_END_DECLS

#endif /* __GSTMPDUTCTIMINGNODE_H__ */
