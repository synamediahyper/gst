
/* This file is generated by glib-mkenums, do not modify it. This code is licensed under the same license as the containing project. Note that it links to GLib, so must comply with the LGPL linking clauses. */

#include "config.h"
#include "controller-enumtypes.h"
#include "gstinterpolationcontrolsource.h"
#include "gstlfocontrolsource.h"

#define C_ENUM(v) ((gint) v)
#define C_FLAGS(v) ((guint) v)

/* enumerations from "gstinterpolationcontrolsource.h" */

GType
gst_interpolation_mode_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_INTERPOLATION_MODE_NONE), "GST_INTERPOLATION_MODE_NONE", "none" },
    { C_ENUM(GST_INTERPOLATION_MODE_LINEAR), "GST_INTERPOLATION_MODE_LINEAR", "linear" },
    { C_ENUM(GST_INTERPOLATION_MODE_CUBIC), "GST_INTERPOLATION_MODE_CUBIC", "cubic" },
    { C_ENUM(GST_INTERPOLATION_MODE_CUBIC_MONOTONIC), "GST_INTERPOLATION_MODE_CUBIC_MONOTONIC", "cubic-monotonic" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstInterpolationMode"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

/* enumerations from "gstlfocontrolsource.h" */

GType
gst_lfo_waveform_get_type (void)
{
  static volatile gsize gtype_id = 0;
  static const GEnumValue values[] = {
    { C_ENUM(GST_LFO_WAVEFORM_SINE), "GST_LFO_WAVEFORM_SINE", "sine" },
    { C_ENUM(GST_LFO_WAVEFORM_SQUARE), "GST_LFO_WAVEFORM_SQUARE", "square" },
    { C_ENUM(GST_LFO_WAVEFORM_SAW), "GST_LFO_WAVEFORM_SAW", "saw" },
    { C_ENUM(GST_LFO_WAVEFORM_REVERSE_SAW), "GST_LFO_WAVEFORM_REVERSE_SAW", "reverse-saw" },
    { C_ENUM(GST_LFO_WAVEFORM_TRIANGLE), "GST_LFO_WAVEFORM_TRIANGLE", "triangle" },
    { 0, NULL, NULL }
  };
  if (g_once_init_enter (&gtype_id)) {
    GType new_type = g_enum_register_static (g_intern_static_string ("GstLFOWaveform"), values);
    g_once_init_leave (&gtype_id, new_type);
  }
  return (GType) gtype_id;
}

/* Generated data ends here */
