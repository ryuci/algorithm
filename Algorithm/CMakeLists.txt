##
## CMakeLists.txt
##  Algorithm
##
##  Created by Choong-il Ryu on 29/01/2019.
##  Copyright © 2019 codetolearn.kr. All rights reserved.
##
## Description
##  Xcode's automatic syntax checking is making trouble by slowing down
##  system response. Turning off the switch does not work well.
##  So, I am moving to VS Code and CMake build system.
##
## Reference
##  https://www.johnlamp.net/cmake-tutorial-1-getting-started.html
##  Best cmake tutorial ever!
##     
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
project(Algorithm)

set(SRC_FILES main.cpp helper.cpp)

# Tell cmake that we need VTK.
set(VTK_DIR "/usr/local/lib")
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
if(VTK_FOUND)
  message(STATUS "VTK Found. Version:" ${VTK_VERSION}. VTK_DIR: ${VTK_DIR})
else(VTK_FOUND)
  message(FATAL_ERROR
    "Cannot build the executable without VTK. Please set the VTK_DIR.")
endif(VTK_FOUND)

# Tell cmake that we need OpenCV.
find_package(OpenCV REQUIRED)
if(OPENCV_FOUND)
  message(STATUS "OPENCV Found. Version:" ${OPENCV_VERSION}. OPENCV_DIR: ${OPENCV_DIR})
else(OPENCV_FOUND)
  message(FATAL_ERROR
    "Cannot build the executable without OPENCV. Please set the OPENCV_DIR.")
endif(OPENCV_FOUND)

# Tell cmake that we need Boost.
#find_package(Boost REQUIRED)
set (BOOST_ROOT ~/boost_1_69_0)

# The compiler uses to search for include files
# in path to the source directory currently being processed. 
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# TODO:1-29-2019: Is there any best practice to sync include path
#                 of cmake and c_cpp_properties.json?
include_directories("/usr/local/include")
include_directories("/usr/local/Cellar/opencv/4.0.1/include/opencv4")
include_directories("/usr/local/include/vtk-8.2")
#include_directories(${Boost_INCLUDE_DIR})
include_directories(${BOOST_ROOT})

# Include the directory in your project. 
# This directory must contain a CMakeLists.txt file.
add_subdirectory(combinatorics)
add_subdirectory(dataStructure)
add_subdirectory(geometry)
add_subdirectory(matrix)
add_subdirectory(memory)
add_subdirectory(misc)
add_subdirectory(numeric)
#add_subdirectory(opencv)
add_subdirectory(runtime)
#add_subdirectory(vtk)

# Display message duing cmake. Not during make.
message(STATUS "Let's go!")

add_executable(algorithm ${SRC_FILES})
# Specify that target needs to be linked against one or more libraries.
target_link_libraries(algorithm 
    combinatorics
    dataStructure
    geometry 
    matrix 
    memory 
    misc 
    numeric 
#    opencv
    runtime
#    vtk
    ${VTK_LIBRARIES}
#    ${OpenCV_LIBS}
    ${BOOST_LIBS}
)

