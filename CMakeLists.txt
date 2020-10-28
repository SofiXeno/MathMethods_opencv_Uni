cmake_minimum_required(VERSION 2.4)
project(clion_opencv)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_STANDARD 11)

# Where to find CMake modules and OpenCV (Windows only)

set(OpenCV_DIR "/Users/sofixeno/Downloads/OpenCV-android-sdk/sdk/java/javadoc/org/opencv")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
# (Windows only)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(clion_opencv Lab10.cpp)

# add libs you need (Windows only)
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)
# (Windows only)

# linking
target_link_libraries(clion_opencv ${OpenCV_LIBS})