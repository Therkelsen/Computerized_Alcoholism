cmake_minimum_required(VERSION 3.5)

project(RobotControl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ur_rtde REQUIRED)
add_executable(RobotControl main.cpp)
target_link_libraries(RobotControl PRIVATE ur_rtde::rtde)
