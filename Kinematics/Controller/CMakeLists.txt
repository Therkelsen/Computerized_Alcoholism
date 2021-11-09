cmake_minimum_required(VERSION 3.5)

project(Controller LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenCV
find_package( OpenCV REQUIRED )

# Pylon
list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} )
find_package(Pylon)
include_directories(${Pylon_INCLUDE_DIRS})

find_package(ur_rtde REQUIRED)
add_executable(Controller main.cpp robotcontroller.cpp robotcontroller.h machinevision.cpp machinevision.h calib.cpp calib.h)
target_link_libraries(Controller ${OpenCV_LIBS} ${Pylon_LIBRARIES} ur_rtde::rtde)
