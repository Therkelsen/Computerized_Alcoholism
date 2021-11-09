#  Usage from an external project:
#    Place the FindPylon.cmake in the same folder as your CMakeLists.txt file
#    In your CMakeLists.txt, add these lines:
#
#    list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} )
#    find_package(Pylon)
#    include_directories(${Pylon_INCLUDE_DIRS})
#    target_link_libraries(MY_TARGET_NAME ${Pylon_LIBRARIES})

set(PYLON_ROOT $ENV{PYLON_ROOT})
if (NOT DEFINED ENV{PYLON_ROOT})
    set(PYLON_ROOT "/opt/pylon")
endif()

set(_PYLON_CONFIG "${PYLON_ROOT}/bin/pylon-config")
if (EXISTS "${_PYLON_CONFIG}")
    set(Pylon_FOUND TRUE)
    execute_process(COMMAND ${_PYLON_CONFIG} --cflags-only-I OUTPUT_VARIABLE HEADERS_OUT)
    execute_process(COMMAND ${_PYLON_CONFIG} --libs-only-l OUTPUT_VARIABLE LIBS_OUT)
    execute_process(COMMAND ${_PYLON_CONFIG} --libs-only-L OUTPUT_VARIABLE LIBDIRS_OUT)
    string(REPLACE " " ";" HEADERS_OUT "${HEADERS_OUT}")
    string(REPLACE "-I" "" HEADERS_OUT "${HEADERS_OUT}")
    string(REPLACE "\n" "" Pylon_INCLUDE_DIRS "${HEADERS_OUT}")

    string(REPLACE " " ";" LIBS_OUT "${LIBS_OUT}")
    string(REPLACE "-l" "" LIBS_OUT "${LIBS_OUT}")
    string(REPLACE "\n" "" Pylon_LIBRARIES "${LIBS_OUT}")

    string(REPLACE " " ";" LIBDIRS_OUT "${LIBDIRS_OUT}")
    string(REPLACE "-L" "" LIBDIRS_OUT "${LIBDIRS_OUT}")
    string(REPLACE "\n" "" LIBDIRS_OUT "${LIBDIRS_OUT}")

    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
    foreach (LIBDIR ${LIBDIRS_OUT})
        link_directories(${LIBDIR})
    endforeach()
    
    message("")
    message("-- Found Pylon libraries and include dirs:")
    message("-- Pylon_INCLUDE_DIRS: ${Pylon_INCLUDE_DIRS}")
    message("-- Pylon_LIBRARIES: ${Pylon_LIBRARIES}")
    message("")
else()
    set(Pylon_FOUND FALSE)
endif()
