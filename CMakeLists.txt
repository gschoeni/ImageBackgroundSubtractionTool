cmake_minimum_required(VERSION 3.1)
project(workout_gif)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS "-Wall -std=c++0x -O0 -g3")

# Project Headers
include_directories(include)

# Project Sources
#file(GLOB_RECURSE SOURCES "src/*.cpp")
#add_library(workout_gif STATIC ${SOURCES})

# Third Party
include_directories(${OPENCV_INCLUDE_DIR})
include_directories(${GLOG_INCLUDE_DIR})
include_directories(${GTEST_INCLUDE_DIR})

link_directories(${GLOG_LIB_DIR})
link_directories(${GTEST_LIB_DIR})
link_directories(${OPENCV_LIB_DIR})

set(LIBS
    ${LIBS}
    opencv_highgui
    opencv_core
    opencv_imgcodecs
    opencv_imgproc
    opencv_video
    opencv_videoio
    glog
    gtest
#    workout_gif
)

link_directories(build)

# tests
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests ${LIBS})

# tools
add_executable(background_subtract tools/background_subtract/main.cpp)
target_link_libraries(background_subtract ${LIBS})

add_executable(export_frames tools/export_frames/main.cpp)
target_link_libraries(export_frames ${LIBS})

add_executable(grab_cut tools/grab_cut/main.cpp)
target_link_libraries(grab_cut ${LIBS})
