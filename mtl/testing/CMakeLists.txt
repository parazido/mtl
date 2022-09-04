cmake_minimum_required(VERSION 3.9)
project(testing)

set(CMAKE_CXX_STANDARD 17)

# Configure library.
set(LIBRARY ${PROJECT_NAME})

add_library(${LIBRARY} INTERFACE)
add_library(mtl::${LIBRARY} ALIAS ${LIBRARY})

set(SOURCE_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/simple_serial_device.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/virtual_buffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/virtual_device.hpp)
target_sources(${LIBRARY} INTERFACE ${SOURCE_LIST})

include(GNUInstallDirs)
target_include_directories(
    ${LIBRARY} INTERFACE
    $<BUILD_INTERFACE:${LIBRARY_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
