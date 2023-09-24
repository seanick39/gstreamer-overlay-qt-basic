cmake_minimum_required(VERSION 3.14)

project(gstreamer-player-frontend VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON) # Qt MetaObjectCompilation
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Clangd

include(FindPkgConfig) # Gstreamer
if(!${PKG_CONFIG_FOUND})
  MESSAGE(FATAL_ERROR "pkg-config required")
  return ("Error: pkg-config not found")
endif()

pkg_check_modules(GSTREAMER gstreamer-1.0>=1.6 gstreamer-video-1.0>=1.6 REQUIRED)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED) # QGraphics
find_package(Qt5MultimediaWidgets REQUIRED)

set(SRC_LIST main.cpp overlay.h overlay.cpp videoplayer.h videoplayer.cpp)
link_directories(${GSTREAMER_LIBRARY_DIRS})
include_directories (${GSTREAMER_INCLUDE_DIRS})
add_executable(gstreamer-player-frontend ${SRC_LIST})
target_link_libraries (gstreamer-player-frontend ${GSTREAMER_LIBRARIES})
qt5_use_modules(gstreamer-player-frontend Core Widgets Multimedia MultimediaWidgets)
