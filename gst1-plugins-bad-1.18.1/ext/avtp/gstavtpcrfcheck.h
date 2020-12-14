/*
 * GStreamer AVTP Plugin
 * Copyright (C) 2019 Intel Corporation
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

#ifndef __GST_AVTP_CRF_CHECK_H__
#define __GST_AVTP_CRF_CHECK_H__

#include <gst/gst.h>

#include "gstavtpcrfbase.h"

G_BEGIN_DECLS
#define GST_TYPE_AVTP_CRF_CHECK (gst_avtp_crf_check_get_type())
#define GST_AVTP_CRF_CHECK(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_AVTP_CRF_CHECK,GstAvtpCrfCheck))
#define GST_AVTP_CRF_CHECK_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_AVTP_CRF_CHECK,GstAvtpCrfCheckClass))
#define GST_IS_AVTP_CRF_CHECK(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_AVTP_CRF_CHECK))
#define GST_IS_AVTP_CRF_CHECK_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_AVTP_CRF_CHECK))
typedef struct _GstAvtpCrfCheck GstAvtpCrfCheck;
typedef struct _GstAvtpCrfCheckClass GstAvtpCrfCheckClass;

struct _GstAvtpCrfCheck
{
  GstAvtpCrfBase avtpcrfbase;

  gboolean drop_invalid;
};

struct _GstAvtpCrfCheckClass
{
  GstAvtpCrfBaseClass parent_class;
};

GType gst_avtp_crf_check_get_type (void);

gboolean gst_avtp_crf_check_plugin_init (GstPlugin * plugin);

G_END_DECLS
#endif /* __GST_AVTP_CRF_CHECK_H__ */
