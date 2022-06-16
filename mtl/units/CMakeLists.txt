cmake_minimum_required(VERSION 3.9)
project(units)

set(CMAKE_CXX_STANDARD 17)

# Configure library.
set(LIBRARY ${PROJECT_NAME})

add_library(${LIBRARY} INTERFACE)
add_library(mtl::${LIBRARY} ALIAS ${LIBRARY})

set(SOURCE_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/units.hpp)
target_sources(${LIBRARY} INTERFACE ${SOURCE_LIST})

include(GNUInstallDirs)
target_include_directories(
    ${LIBRARY} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# target_link_libraries(${LIBRARY} INTERFACE mtl::common)

# Configure testing project.
if(USE_TESTS)
    enable_testing()
    set(BINARY ${PROJECT_NAME}_test)

    set(TESTS_SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/main.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/units.test.cpp)
    add_executable(${BINARY} ${TESTS_SOURCE_LIST})

    target_link_libraries(${BINARY} PRIVATE CONAN_PKG::catch2 mtl::${LIBRARY})

    add_test(NAME ${BINARY}
        COMMAND ${BINARY} -r junit)
endif()
