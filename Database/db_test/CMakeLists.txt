cmake_minimum_required(VERSION 3.5)

project(db_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")

# set up a mapping so that the Release configuration for the Qt imported target is
# used in the COVERAGE CMake configuration.
set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")

#set(EIGEN_DIR "/home/host/Eigen")


# SQL
find_package(Qt5 COMPONENTS Sql REQUIRED)

# OpenCV
find_package( OpenCV REQUIRED )

# Pylon
list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} )
find_package(Pylon)
include_directories(${Pylon_INCLUDE_DIRS})

find_package(RL COMPONENTS HAL REQUIRED)
find_package(ur_rtde REQUIRED)
find_package(Eigen3 3.4 REQUIRED NO_MODULE)

add_executable(db_test main.cpp database.h database.cpp robotcontroller.cpp robotcontroller.h machinevision.cpp machinevision.h calib.cpp calib.h projectilemotion.cpp projectilemotion.h)
target_link_libraries(db_test PRIVATE ${OpenCV_LIBS} ${Pylon_LIBRARIES} ${RL_LIBRARIES} ur_rtde::rtde Eigen3::Eigen Qt5::Sql)
