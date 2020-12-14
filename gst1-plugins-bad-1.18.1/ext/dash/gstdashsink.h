/* GStreamer
 * Copyright (C) 2019 Stéphane Cerveau <scerveau@collabora.com>
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
#ifndef _GST_DASH_SINK_H_
#define _GST_DASH_SINK_H_

#include <gst/gst.h>
#include "gstmpdclient.h"

G_BEGIN_DECLS

#define GST_TYPE_DASH_SINK  gst_dash_sink_get_type ()
G_DECLARE_FINAL_TYPE (GstDashSink, gst_dash_sink, GST, DASH_SINK, GstBin)

gboolean gst_dash_sink_plugin_init (GstPlugin * plugin);

G_END_DECLS

#endif
