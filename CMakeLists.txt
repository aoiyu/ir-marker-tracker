cmake_minimum_required(VERSION 3.22)
project(ir_marker_tracker)

set(CMAKE_CXX_STANDARD 17)

set(OpenCV_DIR lib/opencv-4.6.0/build)
find_package(OpenCV REQUIRED)

add_executable(ir_marker_tracker src/main.cpp)

if(OpenCV_FOUND)
    target_link_libraries(ir_marker_tracker ${OpenCV_LIBS})
endif()