cmake_minimum_required(VERSION 3.5)

project(Main LANGUAGES CXX)

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

#find_package (Eigen 3.4 REQUIRED NO_MODULE)


add_executable(Main main.cpp database.cpp database.h)

# Link libraries
target_link_libraries(Main PRIVATE Qt5::Sql)

