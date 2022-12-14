cmake_minimum_required(VERSION 3.9)
project(mtl)

set(CMAKE_CXX_STANDARD 17)

set(USE_TESTS ON)

set(PROJECT_HOME_DIR ${PROJECT_SOURCE_DIR}/${PROJECT_NAME})

if(NOT DEFINED NO_CONAN)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(NO_OUTPUT_DIRS TARGETS)
else()
    set(USE_TESTS OFF)
endif()

set(LIBRARY_DIR ${PROJECT_SOURCE_DIR})

add_subdirectory(${PROJECT_HOME_DIR}/algorithm)
add_subdirectory(${PROJECT_HOME_DIR}/buffers)
add_subdirectory(${PROJECT_HOME_DIR}/common)
add_subdirectory(${PROJECT_HOME_DIR}/containers)
add_subdirectory(${PROJECT_HOME_DIR}/drivers)
add_subdirectory(${PROJECT_HOME_DIR}/hw)
#add_subdirectory(${PROJECT_HOME_DIR}/network)
add_subdirectory(${PROJECT_HOME_DIR}/os)
add_subdirectory(${PROJECT_HOME_DIR}/sys)
add_subdirectory(${PROJECT_HOME_DIR}/testing)
add_subdirectory(${PROJECT_HOME_DIR}/traits)
add_subdirectory(${PROJECT_HOME_DIR}/units)
