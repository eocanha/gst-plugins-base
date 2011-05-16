/* GStreamer
 * Copyright (C) <2011> Sebastian Dröge <sebastian.droege@collabora.co.uk>
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
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <gst/gst.h>

#ifndef __GST_PLAY_SINK_VIDEO_CONVERT_H__
#define __GST_PLAY_SINK_VIDEO_CONVERT_H__

G_BEGIN_DECLS
#define GST_TYPE_PLAY_SINK_VIDEO_CONVERT \
  (gst_play_sink_video_convert_get_type())
#define GST_PLAY_SINK_VIDEO_CONVERT(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GST_TYPE_PLAY_SINK_VIDEO_CONVERT, GstPlaySinkVideoConvert))
#define GST_PLAY_SINK_VIDEO_CONVERT_CAST(obj) \
  ((GstPlaySinkVideoConvert *) obj)
#define GST_PLAY_SINK_VIDEO_CONVERT_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), GST_TYPE_PLAY_SINK_VIDEO_CONVERT, GstPlaySinkVideoConvertClass))
#define GST_IS_PLAY_SINK_VIDEO_CONVERT(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GST_TYPE_PLAY_SINK_VIDEO_CONVERT))
#define GST_IS_PLAY_SINK_VIDEO_CONVERT_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), GST_TYPE_PLAY_SINK_VIDEO_CONVERT))

#define GST_PLAY_SINK_VIDEO_CONVERT_LOCK(obj) G_STMT_START {                   \
    GST_LOG_OBJECT (obj,                                                \
                    "locking from thread %p",                           \
                    g_thread_self ());                                  \
    g_mutex_lock (GST_PLAY_SINK_VIDEO_CONVERT_CAST(obj)->lock);                \
    GST_LOG_OBJECT (obj,                                                \
                    "locked from thread %p",                            \
                    g_thread_self ());                                  \
} G_STMT_END

#define GST_PLAY_SINK_VIDEO_CONVERT_UNLOCK(obj) G_STMT_START {                 \
    GST_LOG_OBJECT (obj,                                                \
                    "unlocking from thread %p",                         \
                    g_thread_self ());                                  \
    g_mutex_unlock (GST_PLAY_SINK_VIDEO_CONVERT_CAST(obj)->lock);              \
} G_STMT_END

typedef struct _GstPlaySinkVideoConvert GstPlaySinkVideoConvert;
typedef struct _GstPlaySinkVideoConvertClass GstPlaySinkVideoConvertClass;

struct _GstPlaySinkVideoConvert
{
  GstBin parent;

  /* < private > */
  GMutex *lock;

  GstPad *sinkpad, *sink_proxypad;
  gboolean sink_proxypad_blocked;
  GstSegment segment;

  GstPad *srcpad;

  gboolean raw;
  GstElement *conv, *scale;
};

struct _GstPlaySinkVideoConvertClass
{
  GstBinClass parent;
};

GType gst_play_sink_video_convert_get_type (void);

G_END_DECLS
#endif /* __GST_PLAY_SINK_VIDEO_CONVERT_H__ */
