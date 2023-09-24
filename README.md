Gstreamer Overlay QtWidgets


Objective:
Stream a video using a gstreamer backend, and play it using gstreamer in a 
Qt frontend with an overlay which can be adjustable using sliders.
Place an mp4 video as `video.mp4` in this directory, or run the backend manually 
with your video filename.

Directory consists of 2 subdirs:
	1. `backend`: to start streaming the video
	2. `frontend`: to receive it and use the overlay 

To build and run:
$ chmod +x ./*.sh
$ ./run.sh

To kill backend process
$ ./kill-backend.sh
