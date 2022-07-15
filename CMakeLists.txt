cmake_minimum_required(VERSION 3.22)
project(ir_marker_tracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#set(OPENCV_EXTRA_MODULES_PATH ../opencv_contrib/modules)
#set(WITH_CUDA ON)
#set(WITH_CUFFT ON)
#set(WITH_CUBLAS ON)
#set(WITH_NVCUVID ON)
#set(BUILD_JAVA OFF)
#set(BUILD_opencv_python2 OFF)
#set(BUILD_opencv_python3 OFF)
#set(BUILD_opencv_cudacodec ON)
#
#add_subdirectory(lib/opencv EXCLUDE_FROM_ALL)
#include_directories(${OpenCV_INCLUDE_DIRS})

set(OpenCV_DIR lib/opencv/build)
find_package(OpenCV REQUIRED)

add_executable(ir_marker_tracker src/main.cpp src/CameraThread.cpp src/CameraThread.h)

if(OpenCV_FOUND)
    target_link_libraries(ir_marker_tracker ${OpenCV_LIBS})
endif()