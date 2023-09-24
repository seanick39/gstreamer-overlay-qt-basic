cmake_minimum_required(VERSION 3.14)

project(gstreamer-player-backend VERSION 0.1 LANGUAGES CXX)

# for clangd autocompletion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# for gstreamer
include(FindPkgConfig)
if(!${PKG_CONFIG_FOUND})
  MESSAGE(FATAL_ERROR "pkg-config required")
  return ("Error: pkg-config not found")
endif()

pkg_check_modules(GSTREAMER gstreamer-1.0>=1.6 gstreamer-video-1.0>=1.6 REQUIRED)

link_directories(${GSTREAMER_LIBRARY_DIRS})
include_directories (${GSTREAMER_INCLUDE_DIRS})
add_executable(gstreamer-player-backend server.cpp)
target_link_libraries (gstreamer-player-backend ${GSTREAMER_LIBRARIES})
