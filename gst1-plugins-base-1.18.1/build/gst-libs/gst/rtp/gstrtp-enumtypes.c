
/* This file is generated by glib-mkenums, do not modify it. This code is licensed under the same license as the containing project. Note that it links to GLib, so must comply with the LGPL linking clauses. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "gstrtp-enumtypes.h"
#include "gstrtcpbuffer.h"
#include "gstrtpbaseaudiopayload.h"
#include "gstrtpbasedepayload.h"
#include "gstrtpbasepayload.h"
#include "gstrtpbuffer.h"
#include "gstrtpdefs.h"
#include "gstrtphdrext.h"
#include "gstrtpmeta.h"
#include "gstrtppayloads.h"
#include "rtp-prelude.h"
#include "rtp.h"

#define C_ENUM(v) ((gint) v)
#define C_FLAGS(v) ((guint) v)

/* enumerations from "gstrtcpbuffer.h" */

GType
gst_rtcp_type_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_RTCP_TYPE_INVALID), "GST_RTCP_TYPE_INVALID", "invalid" },
    { C_ENUM(GST_RTCP_TYPE_SR), "GST_RTCP_TYPE_SR", "sr" },
    { C_ENUM(GST_RTCP_TYPE_RR), "GST_RTCP_TYPE_RR", "rr" },
    { C_ENUM(GST_RTCP_TYPE_SDES), "GST_RTCP_TYPE_SDES", "sdes" },
    { C_ENUM(GST_RTCP_TYPE_BYE), "GST_RTCP_TYPE_BYE", "bye" },
    { C_ENUM(GST_RTCP_TYPE_APP), "GST_RTCP_TYPE_APP", "app" },
    { C_ENUM(GST_RTCP_TYPE_RTPFB), "GST_RTCP_TYPE_RTPFB", "rtpfb" },
    { C_ENUM(GST_RTCP_TYPE_PSFB), "GST_RTCP_TYPE_PSFB", "psfb" },
    { C_ENUM(GST_RTCP_TYPE_XR), "GST_RTCP_TYPE_XR", "xr" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstRTCPType"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_rtcpfb_type_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_RTCP_FB_TYPE_INVALID), "GST_RTCP_FB_TYPE_INVALID", "fb-type-invalid" },
    { C_ENUM(GST_RTCP_RTPFB_TYPE_NACK), "GST_RTCP_RTPFB_TYPE_NACK", "rtpfb-type-nack" },
    { C_ENUM(GST_RTCP_RTPFB_TYPE_TMMBR), "GST_RTCP_RTPFB_TYPE_TMMBR", "rtpfb-type-tmmbr" },
    { C_ENUM(GST_RTCP_RTPFB_TYPE_TMMBN), "GST_RTCP_RTPFB_TYPE_TMMBN", "rtpfb-type-tmmbn" },
    { C_ENUM(GST_RTCP_RTPFB_TYPE_RTCP_SR_REQ), "GST_RTCP_RTPFB_TYPE_RTCP_SR_REQ", "rtpfb-type-rtcp-sr-req" },
    { C_ENUM(GST_RTCP_RTPFB_TYPE_TWCC), "GST_RTCP_RTPFB_TYPE_TWCC", "rtpfb-type-twcc" },
    { C_ENUM(GST_RTCP_PSFB_TYPE_PLI), "GST_RTCP_PSFB_TYPE_PLI", "psfb-type-pli" },
    { C_ENUM(GST_RTCP_PSFB_TYPE_SLI), "GST_RTCP_PSFB_TYPE_SLI", "psfb-type-sli" },
    { C_ENUM(GST_RTCP_PSFB_TYPE_RPSI), "GST_RTCP_PSFB_TYPE_RPSI", "psfb-type-rpsi" },
    { C_ENUM(GST_RTCP_PSFB_TYPE_AFB), "GST_RTCP_PSFB_TYPE_AFB", "psfb-type-afb" },
    { C_ENUM(GST_RTCP_PSFB_TYPE_FIR), "GST_RTCP_PSFB_TYPE_FIR", "psfb-type-fir" },
    { C_ENUM(GST_RTCP_PSFB_TYPE_TSTR), "GST_RTCP_PSFB_TYPE_TSTR", "psfb-type-tstr" },
    { C_ENUM(GST_RTCP_PSFB_TYPE_TSTN), "GST_RTCP_PSFB_TYPE_TSTN", "psfb-type-tstn" },
    { C_ENUM(GST_RTCP_PSFB_TYPE_VBCN), "GST_RTCP_PSFB_TYPE_VBCN", "psfb-type-vbcn" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstRTCPFBType"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_rtcpsdes_type_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_RTCP_SDES_INVALID), "GST_RTCP_SDES_INVALID", "invalid" },
    { C_ENUM(GST_RTCP_SDES_END), "GST_RTCP_SDES_END", "end" },
    { C_ENUM(GST_RTCP_SDES_CNAME), "GST_RTCP_SDES_CNAME", "cname" },
    { C_ENUM(GST_RTCP_SDES_NAME), "GST_RTCP_SDES_NAME", "name" },
    { C_ENUM(GST_RTCP_SDES_EMAIL), "GST_RTCP_SDES_EMAIL", "email" },
    { C_ENUM(GST_RTCP_SDES_PHONE), "GST_RTCP_SDES_PHONE", "phone" },
    { C_ENUM(GST_RTCP_SDES_LOC), "GST_RTCP_SDES_LOC", "loc" },
    { C_ENUM(GST_RTCP_SDES_TOOL), "GST_RTCP_SDES_TOOL", "tool" },
    { C_ENUM(GST_RTCP_SDES_NOTE), "GST_RTCP_SDES_NOTE", "note" },
    { C_ENUM(GST_RTCP_SDES_PRIV), "GST_RTCP_SDES_PRIV", "priv" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstRTCPSDESType"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_rtcpxr_type_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_RTCP_XR_TYPE_INVALID), "GST_RTCP_XR_TYPE_INVALID", "invalid" },
    { C_ENUM(GST_RTCP_XR_TYPE_LRLE), "GST_RTCP_XR_TYPE_LRLE", "lrle" },
    { C_ENUM(GST_RTCP_XR_TYPE_DRLE), "GST_RTCP_XR_TYPE_DRLE", "drle" },
    { C_ENUM(GST_RTCP_XR_TYPE_PRT), "GST_RTCP_XR_TYPE_PRT", "prt" },
    { C_ENUM(GST_RTCP_XR_TYPE_RRT), "GST_RTCP_XR_TYPE_RRT", "rrt" },
    { C_ENUM(GST_RTCP_XR_TYPE_DLRR), "GST_RTCP_XR_TYPE_DLRR", "dlrr" },
    { C_ENUM(GST_RTCP_XR_TYPE_SSUMM), "GST_RTCP_XR_TYPE_SSUMM", "ssumm" },
    { C_ENUM(GST_RTCP_XR_TYPE_VOIP_METRICS), "GST_RTCP_XR_TYPE_VOIP_METRICS", "voip-metrics" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstRTCPXRType"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

/* enumerations from "gstrtpbuffer.h" */

GType
gst_rtp_buffer_flags_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GFlagsValue values[] = {
    { C_FLAGS(GST_RTP_BUFFER_FLAG_RETRANSMISSION), "GST_RTP_BUFFER_FLAG_RETRANSMISSION", "retransmission" },
    { C_FLAGS(GST_RTP_BUFFER_FLAG_REDUNDANT), "GST_RTP_BUFFER_FLAG_REDUNDANT", "redundant" },
    { C_FLAGS(GST_RTP_BUFFER_FLAG_LAST), "GST_RTP_BUFFER_FLAG_LAST", "last" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_flags_register_static (g_intern_static_string ("GstRTPBufferFlags"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_rtp_buffer_map_flags_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GFlagsValue values[] = {
    { C_FLAGS(GST_RTP_BUFFER_MAP_FLAG_SKIP_PADDING), "GST_RTP_BUFFER_MAP_FLAG_SKIP_PADDING", "skip-padding" },
    { C_FLAGS(GST_RTP_BUFFER_MAP_FLAG_LAST), "GST_RTP_BUFFER_MAP_FLAG_LAST", "last" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_flags_register_static (g_intern_static_string ("GstRTPBufferMapFlags"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

/* enumerations from "gstrtpdefs.h" */

GType
gst_rtp_profile_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_RTP_PROFILE_UNKNOWN), "GST_RTP_PROFILE_UNKNOWN", "unknown" },
    { C_ENUM(GST_RTP_PROFILE_AVP), "GST_RTP_PROFILE_AVP", "avp" },
    { C_ENUM(GST_RTP_PROFILE_SAVP), "GST_RTP_PROFILE_SAVP", "savp" },
    { C_ENUM(GST_RTP_PROFILE_AVPF), "GST_RTP_PROFILE_AVPF", "avpf" },
    { C_ENUM(GST_RTP_PROFILE_SAVPF), "GST_RTP_PROFILE_SAVPF", "savpf" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstRTPProfile"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

/* enumerations from "gstrtppayloads.h" */

GType
gst_rtp_payload_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_RTP_PAYLOAD_PCMU), "GST_RTP_PAYLOAD_PCMU", "pcmu" },
    { C_ENUM(GST_RTP_PAYLOAD_1016), "GST_RTP_PAYLOAD_1016", "1016" },
    { C_ENUM(GST_RTP_PAYLOAD_G721), "GST_RTP_PAYLOAD_G721", "g721" },
    { C_ENUM(GST_RTP_PAYLOAD_GSM), "GST_RTP_PAYLOAD_GSM", "gsm" },
    { C_ENUM(GST_RTP_PAYLOAD_G723), "GST_RTP_PAYLOAD_G723", "g723" },
    { C_ENUM(GST_RTP_PAYLOAD_DVI4_8000), "GST_RTP_PAYLOAD_DVI4_8000", "dvi4-8000" },
    { C_ENUM(GST_RTP_PAYLOAD_DVI4_16000), "GST_RTP_PAYLOAD_DVI4_16000", "dvi4-16000" },
    { C_ENUM(GST_RTP_PAYLOAD_LPC), "GST_RTP_PAYLOAD_LPC", "lpc" },
    { C_ENUM(GST_RTP_PAYLOAD_PCMA), "GST_RTP_PAYLOAD_PCMA", "pcma" },
    { C_ENUM(GST_RTP_PAYLOAD_G722), "GST_RTP_PAYLOAD_G722", "g722" },
    { C_ENUM(GST_RTP_PAYLOAD_L16_STEREO), "GST_RTP_PAYLOAD_L16_STEREO", "l16-stereo" },
    { C_ENUM(GST_RTP_PAYLOAD_L16_MONO), "GST_RTP_PAYLOAD_L16_MONO", "l16-mono" },
    { C_ENUM(GST_RTP_PAYLOAD_QCELP), "GST_RTP_PAYLOAD_QCELP", "qcelp" },
    { C_ENUM(GST_RTP_PAYLOAD_CN), "GST_RTP_PAYLOAD_CN", "cn" },
    { C_ENUM(GST_RTP_PAYLOAD_MPA), "GST_RTP_PAYLOAD_MPA", "mpa" },
    { C_ENUM(GST_RTP_PAYLOAD_G728), "GST_RTP_PAYLOAD_G728", "g728" },
    { C_ENUM(GST_RTP_PAYLOAD_DVI4_11025), "GST_RTP_PAYLOAD_DVI4_11025", "dvi4-11025" },
    { C_ENUM(GST_RTP_PAYLOAD_DVI4_22050), "GST_RTP_PAYLOAD_DVI4_22050", "dvi4-22050" },
    { C_ENUM(GST_RTP_PAYLOAD_G729), "GST_RTP_PAYLOAD_G729", "g729" },
    { C_ENUM(GST_RTP_PAYLOAD_CELLB), "GST_RTP_PAYLOAD_CELLB", "cellb" },
    { C_ENUM(GST_RTP_PAYLOAD_JPEG), "GST_RTP_PAYLOAD_JPEG", "jpeg" },
    { C_ENUM(GST_RTP_PAYLOAD_NV), "GST_RTP_PAYLOAD_NV", "nv" },
    { C_ENUM(GST_RTP_PAYLOAD_H261), "GST_RTP_PAYLOAD_H261", "h261" },
    { C_ENUM(GST_RTP_PAYLOAD_MPV), "GST_RTP_PAYLOAD_MPV", "mpv" },
    { C_ENUM(GST_RTP_PAYLOAD_MP2T), "GST_RTP_PAYLOAD_MP2T", "mp2t" },
    { C_ENUM(GST_RTP_PAYLOAD_H263), "GST_RTP_PAYLOAD_H263", "h263" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstRTPPayload"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

/* Generated data ends here */

