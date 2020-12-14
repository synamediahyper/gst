
/* This file is generated by glib-mkenums, do not modify it. This code is licensed under the same license as the containing project. Note that it links to GLib, so must comply with the LGPL linking clauses. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "webrtc-enumtypes.h"
#include "dtlstransport.h"
#include "icetransport.h"
#include "rtptransceiver.h"
#include "webrtc_fwd.h"

#define C_ENUM(v) ((gint) v)
#define C_FLAGS(v) ((guint) v)

/* enumerations from "webrtc_fwd.h" */

GType
gst_webrtc_dtls_transport_state_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_WEBRTC_DTLS_TRANSPORT_STATE_NEW), "GST_WEBRTC_DTLS_TRANSPORT_STATE_NEW", "new" },
    { C_ENUM(GST_WEBRTC_DTLS_TRANSPORT_STATE_CLOSED), "GST_WEBRTC_DTLS_TRANSPORT_STATE_CLOSED", "closed" },
    { C_ENUM(GST_WEBRTC_DTLS_TRANSPORT_STATE_FAILED), "GST_WEBRTC_DTLS_TRANSPORT_STATE_FAILED", "failed" },
    { C_ENUM(GST_WEBRTC_DTLS_TRANSPORT_STATE_CONNECTING), "GST_WEBRTC_DTLS_TRANSPORT_STATE_CONNECTING", "connecting" },
    { C_ENUM(GST_WEBRTC_DTLS_TRANSPORT_STATE_CONNECTED), "GST_WEBRTC_DTLS_TRANSPORT_STATE_CONNECTED", "connected" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstWebRTCDTLSTransportState"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_webrtc_ice_gathering_state_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_WEBRTC_ICE_GATHERING_STATE_NEW), "GST_WEBRTC_ICE_GATHERING_STATE_NEW", "new" },
    { C_ENUM(GST_WEBRTC_ICE_GATHERING_STATE_GATHERING), "GST_WEBRTC_ICE_GATHERING_STATE_GATHERING", "gathering" },
    { C_ENUM(GST_WEBRTC_ICE_GATHERING_STATE_COMPLETE), "GST_WEBRTC_ICE_GATHERING_STATE_COMPLETE", "complete" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstWebRTCICEGatheringState"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_webrtc_ice_connection_state_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_WEBRTC_ICE_CONNECTION_STATE_NEW), "GST_WEBRTC_ICE_CONNECTION_STATE_NEW", "new" },
    { C_ENUM(GST_WEBRTC_ICE_CONNECTION_STATE_CHECKING), "GST_WEBRTC_ICE_CONNECTION_STATE_CHECKING", "checking" },
    { C_ENUM(GST_WEBRTC_ICE_CONNECTION_STATE_CONNECTED), "GST_WEBRTC_ICE_CONNECTION_STATE_CONNECTED", "connected" },
    { C_ENUM(GST_WEBRTC_ICE_CONNECTION_STATE_COMPLETED), "GST_WEBRTC_ICE_CONNECTION_STATE_COMPLETED", "completed" },
    { C_ENUM(GST_WEBRTC_ICE_CONNECTION_STATE_FAILED), "GST_WEBRTC_ICE_CONNECTION_STATE_FAILED", "failed" },
    { C_ENUM(GST_WEBRTC_ICE_CONNECTION_STATE_DISCONNECTED), "GST_WEBRTC_ICE_CONNECTION_STATE_DISCONNECTED", "disconnected" },
    { C_ENUM(GST_WEBRTC_ICE_CONNECTION_STATE_CLOSED), "GST_WEBRTC_ICE_CONNECTION_STATE_CLOSED", "closed" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstWebRTCICEConnectionState"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_webrtc_signaling_state_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_WEBRTC_SIGNALING_STATE_STABLE), "GST_WEBRTC_SIGNALING_STATE_STABLE", "stable" },
    { C_ENUM(GST_WEBRTC_SIGNALING_STATE_CLOSED), "GST_WEBRTC_SIGNALING_STATE_CLOSED", "closed" },
    { C_ENUM(GST_WEBRTC_SIGNALING_STATE_HAVE_LOCAL_OFFER), "GST_WEBRTC_SIGNALING_STATE_HAVE_LOCAL_OFFER", "have-local-offer" },
    { C_ENUM(GST_WEBRTC_SIGNALING_STATE_HAVE_REMOTE_OFFER), "GST_WEBRTC_SIGNALING_STATE_HAVE_REMOTE_OFFER", "have-remote-offer" },
    { C_ENUM(GST_WEBRTC_SIGNALING_STATE_HAVE_LOCAL_PRANSWER), "GST_WEBRTC_SIGNALING_STATE_HAVE_LOCAL_PRANSWER", "have-local-pranswer" },
    { C_ENUM(GST_WEBRTC_SIGNALING_STATE_HAVE_REMOTE_PRANSWER), "GST_WEBRTC_SIGNALING_STATE_HAVE_REMOTE_PRANSWER", "have-remote-pranswer" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstWebRTCSignalingState"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_webrtc_peer_connection_state_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_WEBRTC_PEER_CONNECTION_STATE_NEW), "GST_WEBRTC_PEER_CONNECTION_STATE_NEW", "new" },
    { C_ENUM(GST_WEBRTC_PEER_CONNECTION_STATE_CONNECTING), "GST_WEBRTC_PEER_CONNECTION_STATE_CONNECTING", "connecting" },
    { C_ENUM(GST_WEBRTC_PEER_CONNECTION_STATE_CONNECTED), "GST_WEBRTC_PEER_CONNECTION_STATE_CONNECTED", "connected" },
    { C_ENUM(GST_WEBRTC_PEER_CONNECTION_STATE_DISCONNECTED), "GST_WEBRTC_PEER_CONNECTION_STATE_DISCONNECTED", "disconnected" },
    { C_ENUM(GST_WEBRTC_PEER_CONNECTION_STATE_FAILED), "GST_WEBRTC_PEER_CONNECTION_STATE_FAILED", "failed" },
    { C_ENUM(GST_WEBRTC_PEER_CONNECTION_STATE_CLOSED), "GST_WEBRTC_PEER_CONNECTION_STATE_CLOSED", "closed" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstWebRTCPeerConnectionState"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_webrtc_ice_role_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_WEBRTC_ICE_ROLE_CONTROLLED), "GST_WEBRTC_ICE_ROLE_CONTROLLED", "controlled" },
    { C_ENUM(GST_WEBRTC_ICE_ROLE_CONTROLLING), "GST_WEBRTC_ICE_ROLE_CONTROLLING", "controlling" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstWebRTCICERole"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_webrtc_ice_component_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_WEBRTC_ICE_COMPONENT_RTP), "GST_WEBRTC_ICE_COMPONENT_RTP", "rtp" },
    { C_ENUM(GST_WEBRTC_ICE_COMPONENT_RTCP), "GST_WEBRTC_ICE_COMPONENT_RTCP", "rtcp" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstWebRTCICEComponent"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_webrtc_sdp_type_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_WEBRTC_SDP_TYPE_OFFER), "GST_WEBRTC_SDP_TYPE_OFFER", "offer" },
    { C_ENUM(GST_WEBRTC_SDP_TYPE_PRANSWER), "GST_WEBRTC_SDP_TYPE_PRANSWER", "pranswer" },
    { C_ENUM(GST_WEBRTC_SDP_TYPE_ANSWER), "GST_WEBRTC_SDP_TYPE_ANSWER", "answer" },
    { C_ENUM(GST_WEBRTC_SDP_TYPE_ROLLBACK), "GST_WEBRTC_SDP_TYPE_ROLLBACK", "rollback" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstWebRTCSDPType"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_webrtc_rtp_transceiver_direction_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_WEBRTC_RTP_TRANSCEIVER_DIRECTION_NONE), "GST_WEBRTC_RTP_TRANSCEIVER_DIRECTION_NONE", "none" },
    { C_ENUM(GST_WEBRTC_RTP_TRANSCEIVER_DIRECTION_INACTIVE), "GST_WEBRTC_RTP_TRANSCEIVER_DIRECTION_INACTIVE", "inactive" },
    { C_ENUM(GST_WEBRTC_RTP_TRANSCEIVER_DIRECTION_SENDONLY), "GST_WEBRTC_RTP_TRANSCEIVER_DIRECTION_SENDONLY", "sendonly" },
    { C_ENUM(GST_WEBRTC_RTP_TRANSCEIVER_DIRECTION_RECVONLY), "GST_WEBRTC_RTP_TRANSCEIVER_DIRECTION_RECVONLY", "recvonly" },
    { C_ENUM(GST_WEBRTC_RTP_TRANSCEIVER_DIRECTION_SENDRECV), "GST_WEBRTC_RTP_TRANSCEIVER_DIRECTION_SENDRECV", "sendrecv" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstWebRTCRTPTransceiverDirection"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_webrtc_dtls_setup_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_WEBRTC_DTLS_SETUP_NONE), "GST_WEBRTC_DTLS_SETUP_NONE", "none" },
    { C_ENUM(GST_WEBRTC_DTLS_SETUP_ACTPASS), "GST_WEBRTC_DTLS_SETUP_ACTPASS", "actpass" },
    { C_ENUM(GST_WEBRTC_DTLS_SETUP_ACTIVE), "GST_WEBRTC_DTLS_SETUP_ACTIVE", "active" },
    { C_ENUM(GST_WEBRTC_DTLS_SETUP_PASSIVE), "GST_WEBRTC_DTLS_SETUP_PASSIVE", "passive" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstWebRTCDTLSSetup"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_webrtc_stats_type_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_WEBRTC_STATS_CODEC), "GST_WEBRTC_STATS_CODEC", "codec" },
    { C_ENUM(GST_WEBRTC_STATS_INBOUND_RTP), "GST_WEBRTC_STATS_INBOUND_RTP", "inbound-rtp" },
    { C_ENUM(GST_WEBRTC_STATS_OUTBOUND_RTP), "GST_WEBRTC_STATS_OUTBOUND_RTP", "outbound-rtp" },
    { C_ENUM(GST_WEBRTC_STATS_REMOTE_INBOUND_RTP), "GST_WEBRTC_STATS_REMOTE_INBOUND_RTP", "remote-inbound-rtp" },
    { C_ENUM(GST_WEBRTC_STATS_REMOTE_OUTBOUND_RTP), "GST_WEBRTC_STATS_REMOTE_OUTBOUND_RTP", "remote-outbound-rtp" },
    { C_ENUM(GST_WEBRTC_STATS_CSRC), "GST_WEBRTC_STATS_CSRC", "csrc" },
    { C_ENUM(GST_WEBRTC_STATS_PEER_CONNECTION), "GST_WEBRTC_STATS_PEER_CONNECTION", "peer-connection" },
    { C_ENUM(GST_WEBRTC_STATS_DATA_CHANNEL), "GST_WEBRTC_STATS_DATA_CHANNEL", "data-channel" },
    { C_ENUM(GST_WEBRTC_STATS_STREAM), "GST_WEBRTC_STATS_STREAM", "stream" },
    { C_ENUM(GST_WEBRTC_STATS_TRANSPORT), "GST_WEBRTC_STATS_TRANSPORT", "transport" },
    { C_ENUM(GST_WEBRTC_STATS_CANDIDATE_PAIR), "GST_WEBRTC_STATS_CANDIDATE_PAIR", "candidate-pair" },
    { C_ENUM(GST_WEBRTC_STATS_LOCAL_CANDIDATE), "GST_WEBRTC_STATS_LOCAL_CANDIDATE", "local-candidate" },
    { C_ENUM(GST_WEBRTC_STATS_REMOTE_CANDIDATE), "GST_WEBRTC_STATS_REMOTE_CANDIDATE", "remote-candidate" },
    { C_ENUM(GST_WEBRTC_STATS_CERTIFICATE), "GST_WEBRTC_STATS_CERTIFICATE", "certificate" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstWebRTCStatsType"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_webrtc_fec_type_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_WEBRTC_FEC_TYPE_NONE), "GST_WEBRTC_FEC_TYPE_NONE", "none" },
    { C_ENUM(GST_WEBRTC_FEC_TYPE_ULP_RED), "GST_WEBRTC_FEC_TYPE_ULP_RED", "ulp-red" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstWebRTCFECType"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_webrtc_sctp_transport_state_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_WEBRTC_SCTP_TRANSPORT_STATE_NEW), "GST_WEBRTC_SCTP_TRANSPORT_STATE_NEW", "new" },
    { C_ENUM(GST_WEBRTC_SCTP_TRANSPORT_STATE_CONNECTING), "GST_WEBRTC_SCTP_TRANSPORT_STATE_CONNECTING", "connecting" },
    { C_ENUM(GST_WEBRTC_SCTP_TRANSPORT_STATE_CONNECTED), "GST_WEBRTC_SCTP_TRANSPORT_STATE_CONNECTED", "connected" },
    { C_ENUM(GST_WEBRTC_SCTP_TRANSPORT_STATE_CLOSED), "GST_WEBRTC_SCTP_TRANSPORT_STATE_CLOSED", "closed" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstWebRTCSCTPTransportState"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_webrtc_priority_type_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_WEBRTC_PRIORITY_TYPE_VERY_LOW), "GST_WEBRTC_PRIORITY_TYPE_VERY_LOW", "very-low" },
    { C_ENUM(GST_WEBRTC_PRIORITY_TYPE_LOW), "GST_WEBRTC_PRIORITY_TYPE_LOW", "low" },
    { C_ENUM(GST_WEBRTC_PRIORITY_TYPE_MEDIUM), "GST_WEBRTC_PRIORITY_TYPE_MEDIUM", "medium" },
    { C_ENUM(GST_WEBRTC_PRIORITY_TYPE_HIGH), "GST_WEBRTC_PRIORITY_TYPE_HIGH", "high" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstWebRTCPriorityType"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_webrtc_data_channel_state_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_WEBRTC_DATA_CHANNEL_STATE_NEW), "GST_WEBRTC_DATA_CHANNEL_STATE_NEW", "new" },
    { C_ENUM(GST_WEBRTC_DATA_CHANNEL_STATE_CONNECTING), "GST_WEBRTC_DATA_CHANNEL_STATE_CONNECTING", "connecting" },
    { C_ENUM(GST_WEBRTC_DATA_CHANNEL_STATE_OPEN), "GST_WEBRTC_DATA_CHANNEL_STATE_OPEN", "open" },
    { C_ENUM(GST_WEBRTC_DATA_CHANNEL_STATE_CLOSING), "GST_WEBRTC_DATA_CHANNEL_STATE_CLOSING", "closing" },
    { C_ENUM(GST_WEBRTC_DATA_CHANNEL_STATE_CLOSED), "GST_WEBRTC_DATA_CHANNEL_STATE_CLOSED", "closed" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstWebRTCDataChannelState"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_webrtc_bundle_policy_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_WEBRTC_BUNDLE_POLICY_NONE), "GST_WEBRTC_BUNDLE_POLICY_NONE", "none" },
    { C_ENUM(GST_WEBRTC_BUNDLE_POLICY_BALANCED), "GST_WEBRTC_BUNDLE_POLICY_BALANCED", "balanced" },
    { C_ENUM(GST_WEBRTC_BUNDLE_POLICY_MAX_COMPAT), "GST_WEBRTC_BUNDLE_POLICY_MAX_COMPAT", "max-compat" },
    { C_ENUM(GST_WEBRTC_BUNDLE_POLICY_MAX_BUNDLE), "GST_WEBRTC_BUNDLE_POLICY_MAX_BUNDLE", "max-bundle" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstWebRTCBundlePolicy"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

GType
gst_webrtc_ice_transport_policy_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_WEBRTC_ICE_TRANSPORT_POLICY_ALL), "GST_WEBRTC_ICE_TRANSPORT_POLICY_ALL", "all" },
    { C_ENUM(GST_WEBRTC_ICE_TRANSPORT_POLICY_RELAY), "GST_WEBRTC_ICE_TRANSPORT_POLICY_RELAY", "relay" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstWebRTCICETransportPolicy"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

/* Generated data ends here */
