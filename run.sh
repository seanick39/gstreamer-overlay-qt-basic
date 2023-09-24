#!/bin/sh

# this will start the backend server in another process;
# to kill it, run:
# $ killall gstreamer-player-backend


mkdir -p backend/build
cmake -S backend -B backend/build \
    && cmake -S frontend -B frontend/build \
    && make -C backend/build \
    && make -C frontend/build
sleep 2 && ./backend/build/gstreamer-player-backend video.mp4 &

sleep 7 && ./frontend/build/gstreamer-player-frontend
