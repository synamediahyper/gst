/* GStreamer
 * Copyright (C) 2020 Seungha Yang <seungha@centricular.com>
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

#ifndef __GST_MF_DEVICE_H__
#define __GST_MF_DEVICE_H__

#include <gst/gst.h>

G_BEGIN_DECLS

#define GST_TYPE_MF_DEVICE          (gst_mf_device_get_type())
#define GST_TYPE_MF_DEVICE_PROVIDER (gst_mf_device_provider_get_type())

G_DECLARE_FINAL_TYPE (GstMFDevice, gst_mf_device, GST, MF_DEVICE, GstDevice);
G_DECLARE_FINAL_TYPE (GstMFDeviceProvider,
    gst_mf_device_provider, GST, MF_DEVICE_PROVIDER, GstDeviceProvider);

G_DEFINE_AUTOPTR_CLEANUP_FUNC(GstMFDevice, gst_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GstMFDeviceProvider, gst_object_unref)

G_END_DECLS

#endif /* __GST_MF_DEVICE_H__ */