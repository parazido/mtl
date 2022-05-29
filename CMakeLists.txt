cmake_minimum_required(VERSION 3.9)
project(mtl)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_HOME_DIR ${PROJECT_SOURCE_DIR}/${PROJECT_NAME})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS TARGETS)

add_subdirectory(${PROJECT_HOME_DIR}/common)
add_subdirectory(${PROJECT_HOME_DIR}/traits)
