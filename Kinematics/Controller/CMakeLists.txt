cmake_minimum_required(VERSION 3.5)

project(Controller LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ur_rtde REQUIRED)
add_executable(Controller main.cpp robotcontroller.cpp robotcontroller.h)
target_link_libraries(Controller PRIVATE ur_rtde::rtde)

