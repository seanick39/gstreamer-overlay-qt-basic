/**
 * gstreamer backend server to stream a video to tcp port 5000 
 *
 * 
 * Objective: 
 * Stream a video using a gstreamer backend and play it using gstreamer in a 
 * Qt frontend with an overlay which can be adjustable by sliders.
 * */

#include <string>
#include <gst/gst.h>


int main(int argc, char *argv[]) 
{
  if (argc != 2){
	  fprintf(stderr, "Usage: %s <video-filename>\nplay video with gstreamer using tcpserversink on localhost port 5000\n", argv[0]);
      return EXIT_FAILURE;
  }

  // initialize gstreamer env
  gst_init(&argc, &argv);

  GError *error = nullptr;

  // set up pipeline with videofile arg
  std::string pipeline_str("filesrc location=");
  (pipeline_str += argv[1]) += " ! decodebin ! x264enc ! mpegtsmux ! queue ! tcpserversink host=127.0.0.1 port=5000";

  GstElement* pipeline = gst_parse_launch(pipeline_str.c_str(), &error);
  if (error) {
    fprintf(stderr, "Error creating pipeline: %s\n", error->message);
    return -1;
  }

  puts("creating gstreamer loop");
  GMainLoop* loop = g_main_loop_new(NULL, FALSE);

  puts("starting server");
  gst_element_set_state(pipeline, GST_STATE_PLAYING);
  g_main_loop_run(loop);
  gst_object_unref(pipeline);
  g_main_loop_unref(loop);
  return EXIT_SUCCESS;
}
