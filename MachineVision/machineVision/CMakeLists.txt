cmake_minimum_required(VERSION 3.5)

project(machineVision LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenCV
find_package( OpenCV REQUIRED )

# Pylon
list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} )
find_package(Pylon)
include_directories(${Pylon_INCLUDE_DIRS})

add_executable(machineVision main.cpp machinevision.h machinevision.cpp)
target_link_libraries( machineVision ${OpenCV_LIBS} ${Pylon_LIBRARIES})
