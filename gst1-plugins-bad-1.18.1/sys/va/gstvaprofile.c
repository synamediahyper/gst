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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "gstvaprofile.h"

/* *INDENT-OFF* */
static const struct ProfileMap
{
  VAProfile profile;
  GstVaCodecs codec;
  const gchar *name;
  const gchar *media_type;
  const gchar *caps_str;
} profile_map[] = {
#define P(codec, name, media_type, caps_str) {                \
    G_PASTE (G_PASTE (VAProfile, codec), name), codec,        \
    G_STRINGIFY (G_PASTE (G_PASTE (VAProfile, codec), name)), \
    media_type, caps_str }
  P (MPEG2, Simple, "video/mpeg",
      "mpegversion = (int) 2, profile = (string) simple"),
  P (MPEG2, Main, "video/mpeg",
      "mpegversion = (int) 2, profile = (string) main"),
  P (MPEG4, Simple, "video/mpeg",
      "mpegversion = (int) 4, profile = (string) simple"),
  P (MPEG4, AdvancedSimple, "video/mpeg",
      "mpegversion = (int) 4, profile = (string) advanced-simple"),
  P (MPEG4, Main, "video/mpeg",
      "mpegversion = (int) 4, profile = (string) main, "),
  P (H264, Main, "video/x-h264", "profile = (string) { main, baseline }"),
  P (H264, High, "video/x-h264",
      "profile = (string) { progressive-high, constrained-high, high }"),
  P (VC1, Simple, "video/x-wmv",
      "wmvversion = (int) 3, profile = (string) simple"),
  P (VC1, Main, "video/x-wmv",
      "wmvversion = (int) 3, profile = (string) main"),
  P (VC1, Advanced, "video/x-wmv",
      "wmvversion = (int) 3, format = (string) WVC1, "
      "profile = (string) advanced"),
  P (H263, Baseline, "video/x-h263",
      "variant = (string) itu, h263version = (string) h263, "
      "profile = (string) baseline"),
  P (JPEG, Baseline, "image/jpeg", NULL),
  P (H264, ConstrainedBaseline, "video/x-h264",
      "profile = (string) { baseline, constrained-baseline }"),
  P (VP8, Version0_3, "video/x-vp8", NULL),
  /* Unsupported profiles by current GstH264Decoder */
  /* P (H264, MultiviewHigh, "video/x-h264", */
  /*     "profile = (string) {  multiview-high, stereo-high }"), */
  /* P (H264, StereoHigh, "video/x-h264", */
  /*     "profile = (string) {  multiview-high, stereo-high }"), */
  P (HEVC, Main, "video/x-h265", "profile = (string) main"),
  P (HEVC, Main10, "video/x-h265", "profile = (string) main-10"),
  P (VP9, Profile0, "video/x-vp9", "profile = (string) profile0"),
  P (VP9, Profile1, "video/x-vp9", "profile = (string) profile1"),
  P (VP9, Profile2, "video/x-vp9", "profile = (string) profile2"),
  P (VP9, Profile3, "video/x-vp9", "profile = (string) profile3"),
  P (HEVC, Main12, "video/x-h265", "profile = (string) main-12"),
  P (HEVC, Main422_10, "video/x-h265", "profile = (string) main-422-10"),
  P (HEVC, Main422_12, "video/x-h265", "profile = (string) main-422-12"),
  P (HEVC, Main444, "video/x-h265", "profile = (string) main-444"),
  P (HEVC, Main444_10, "video/x-h265", "profile = (string) main-444-10"),
  P (HEVC, Main444_12, "video/x-h265", "profile = (string) main-444-12"),
  P (HEVC, SccMain, "video/x-h265", "profile = (string) screen-extended-main"),
  P (HEVC, SccMain10, "video/x-h265",
      "profile = (string) screen-extended-main-10"),
  P (HEVC, SccMain444, "video/x-h265",
      "profile = (string) screen-extended-main-444"),
#if VA_CHECK_VERSION(1,7,0)
  P (AV1, Profile0, "video/x-av1", NULL),
  P (AV1, Profile1, "video/x-av1", NULL),
#endif
#if VA_CHECK_VERSION(1, 8, 0)
  P (HEVC, SccMain444_10, "video/x-h265",
      "profile = (string) screen-extended-main-444-10"),
#endif
#undef P
};
/* *INDENT-ON* */

static const struct ProfileMap *
get_profile_map (VAProfile profile)
{
  int i;

  for (i = 0; i < G_N_ELEMENTS (profile_map); i++) {
    if (profile_map[i].profile == profile)
      return &profile_map[i];
  }

  return NULL;
}

guint32
gst_va_profile_codec (VAProfile profile)
{
  const struct ProfileMap *map = get_profile_map (profile);
  return map ? map->codec : GST_MAKE_FOURCC ('N', 'O', 'N', 'E');
}

const gchar *
gst_va_profile_name (VAProfile profile)
{
  const struct ProfileMap *map = get_profile_map (profile);
  return map ? map->name : NULL;
}

GstCaps *
gst_va_profile_caps (VAProfile profile)
{
  const struct ProfileMap *map = get_profile_map (profile);
  GstCaps *caps;
  gchar *caps_str;

  if (!map)
    return NULL;

  if (map->caps_str)
    caps_str = g_strdup_printf ("%s, %s", map->media_type, map->caps_str);
  else
    caps_str = g_strdup (map->media_type);

  caps = gst_caps_from_string (caps_str);
  g_free (caps_str);

  return caps;
}
