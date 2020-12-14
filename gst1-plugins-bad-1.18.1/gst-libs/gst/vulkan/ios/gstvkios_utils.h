/*
 * GStreamer
 * Copyright (C) 2019 Matthew Waters <matthew@centricular.com>
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

#ifndef __VULKAN_IOS_UTILS_H__
#define __VULKAN_IOS_UTILS_H__

#include <gst/gst.h>
#include <UIKit/UIKit.h>

#include "gstvkwindow_ios.h"

G_BEGIN_DECLS

@interface GstVulkanUIView : UIView
- (void) setGstWindow:(GstVulkanWindowIos *)window_ios;
@end

typedef void (*GstVulkanWindowFunc) (gpointer data);

G_GNUC_INTERNAL
void _invoke_on_main (GstVulkanWindowFunc func, gpointer data, GDestroyNotify notify);

G_END_DECLS

#endif
