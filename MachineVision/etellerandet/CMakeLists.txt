cmake_minimum_required(VERSION 3.5)

project(calibration LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package( OpenCV REQUIRED )
add_executable( calibration main.cpp )
target_link_libraries(  calibration ${OpenCV_LIBS} )
