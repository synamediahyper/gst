/* GStreamer
 * Copyright (C) 2020 Igalia, S.L.
 *     Author: Víctor Jáquez <vjaquez@igalia.com>
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

#pragma once

#include <gst/gst.h>
#include <va/va.h>

G_BEGIN_DECLS

#define GST_TYPE_VA_DISPLAY (gst_va_display_get_type())
G_DECLARE_DERIVABLE_TYPE (GstVaDisplay, gst_va_display, GST, VA_DISPLAY, GstObject)

struct _GstVaDisplayClass
{
  /*< private > */
  GstObjectClass parent_class;

  /*< public > */
  gpointer (*create_va_display) (GstVaDisplay * self);
};

void                  gst_va_display_lock                 (GstVaDisplay * self);
void                  gst_va_display_unlock               (GstVaDisplay * self);
gboolean              gst_va_display_initialize           (GstVaDisplay * self);
VADisplay             gst_va_display_get_va_dpy           (GstVaDisplay * self);
GArray *              gst_va_display_get_profiles         (GstVaDisplay * self,
                                                           guint32 codec,
                                                           VAEntrypoint entrypoint);
GArray *              gst_va_display_get_image_formats    (GstVaDisplay * display);

G_END_DECLS
