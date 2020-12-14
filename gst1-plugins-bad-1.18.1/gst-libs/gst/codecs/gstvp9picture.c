/* GStreamer
 * Copyright (C) 2019 Seungha Yang <seungha.yang@navercorp.com>
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
#include <config.h>
#endif

#include "gstvp9picture.h"

GST_DEBUG_CATEGORY_EXTERN (gst_vp9_decoder_debug);
#define GST_CAT_DEFAULT gst_vp9_decoder_debug

GST_DEFINE_MINI_OBJECT_TYPE (GstVp9Picture, gst_vp9_picture);

static void
_gst_vp9_picture_free (GstVp9Picture * picture)
{
  GST_TRACE ("Free picture %p", picture);

  if (picture->notify)
    picture->notify (picture->user_data);

  g_free (picture);
}

/**
 * gst_vp9_picture_new:
 *
 * Create new #GstVp9Picture
 *
 * Returns: a new #GstVp9Picture
 */
GstVp9Picture *
gst_vp9_picture_new (void)
{
  GstVp9Picture *pic;

  pic = g_new0 (GstVp9Picture, 1);
  pic->pts = GST_CLOCK_TIME_NONE;

  gst_mini_object_init (GST_MINI_OBJECT_CAST (pic), 0,
      GST_TYPE_VP9_PICTURE, NULL, NULL,
      (GstMiniObjectFreeFunction) _gst_vp9_picture_free);

  GST_TRACE ("New picture %p", pic);

  return pic;
}

/**
 * gst_vp9_picture_set_user_data:
 * @picture: a #GstVp9Picture
 * @user_data: private data
 * @notify: (closure user_data): a #GDestroyNotify
 *
 * Sets @user_data on the picture and the #GDestroyNotify that will be called when
 * the picture is freed.
 *
 * If a @user_data was previously set, then the previous set @notify will be called
 * before the @user_data is replaced.
 */
void
gst_vp9_picture_set_user_data (GstVp9Picture * picture, gpointer user_data,
    GDestroyNotify notify)
{
  g_return_if_fail (GST_IS_VP9_PICTURE (picture));

  if (picture->notify)
    picture->notify (picture->user_data);

  picture->user_data = user_data;
  picture->notify = notify;
}

/**
 * gst_vp9_picture_get_user_data:
 * @picture: a #GstVp9Picture
 *
 * Gets private data set on the picture via
 * gst_vp9_picture_set_user_data() previously.
 *
 * Returns: (transfer none): The previously set user_data
 */
gpointer
gst_vp9_picture_get_user_data (GstVp9Picture * picture)
{
  return picture->user_data;
}

/**
 * gst_vp9_dpb_new: (skip)
 *
 * Create new #GstVp9Dpb
 *
 * Returns: a new #GstVp9Dpb
 */
GstVp9Dpb *
gst_vp9_dpb_new (void)
{
  GstVp9Dpb *dpb;

  dpb = g_new0 (GstVp9Dpb, 1);

  return dpb;
}

/**
 * gst_vp9_dpb_free:
 * @dpb: a #GstVp9Dpb to free
 *
 * Free the @dpb
 */
void
gst_vp9_dpb_free (GstVp9Dpb * dpb)
{
  g_return_if_fail (dpb != NULL);

  gst_vp9_dpb_clear (dpb);
  g_free (dpb);
}

/**
 * gst_vp9_dpb_clear:
 * @dpb: a #GstVp9Dpb
 *
 * Clear all stored #GstVp9Picture
 */
void
gst_vp9_dpb_clear (GstVp9Dpb * dpb)
{
  gint i;

  g_return_if_fail (dpb != NULL);

  for (i = 0; i < GST_VP9_REF_FRAMES; i++)
    gst_vp9_picture_clear (&dpb->pic_list[i]);
}

/**
 * gst_vp9_dpb_add:
 * @dpb: a #GstVp9Dpb
 * @picture: (transfer full): a #GstVp9Picture
 *
 * Store the @picture
 */
void
gst_vp9_dpb_add (GstVp9Dpb * dpb, GstVp9Picture * picture)
{
  guint8 refresh_frame_flags;
  gint i;

  g_return_if_fail (dpb != NULL);
  g_return_if_fail (GST_IS_VP9_PICTURE (picture));

  if (picture->frame_hdr.frame_type == GST_VP9_KEY_FRAME) {
    refresh_frame_flags = (1 << GST_VP9_REF_FRAMES) - 1;
    GST_TRACE ("keyframe, fill to all pictures");
  } else {
    refresh_frame_flags = picture->frame_hdr.refresh_frame_flags;
    GST_TRACE ("non-keyframe, refresh frame flags 0x%x", refresh_frame_flags);
  }

  for (i = 0; i < GST_VP9_REF_FRAMES; i++) {
    if (refresh_frame_flags & 0x1) {
      gst_vp9_picture_replace (&dpb->pic_list[i], picture);
    }

    refresh_frame_flags >>= 1;
  }

  gst_vp9_picture_unref (picture);
}
