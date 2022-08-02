cmake_minimum_required(VERSION 3.9)
project(hw)

set(CMAKE_CXX_STANDARD 17)

# Configure library.
set(LIBRARY ${PROJECT_NAME})

add_library(${LIBRARY} INTERFACE)
add_library(mtl::${LIBRARY} ALIAS ${LIBRARY})

set(INCLUDE_DIRS ${LIBRARY_DIR})

set(SOURCE_LIST
    "${CMAKE_CURRENT_SOURCE_DIR}/device.hpp")

if(DEFINED TARGET_PLATFORM)
    set(LOCAL_PLATFORMS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/devices")
    set(LOCAL_GENERIC_PLATFORMS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/generic")
    
    if(DEFINED TARGET_PLATFORM_DIR)
        set(MODULE_TARGET_PLATFORM_DIR "${TARGET_PLATFORM_DIR}/mtl/hw")
        if(EXISTS ${MODULE_TARGET_PLATFORM_DIR})
            file(REMOVE_RECURSE ${MODULE_TARGET_PLATFORM_DIR})
        endif()
        file(MAKE_DIRECTORY "${MODULE_TARGET_PLATFORM_DIR}")
    else()
        message(FATAL_ERROR "Directory for platform specific code must be defined.")
    endif()

    if("${TARGET_PLATFORM}" STREQUAL "STM32F072")
        set(LOCAL_PLATFORM_DIR "${LOCAL_PLATFORMS_DIR}/stm32f072")
        set(LOCAL_PLATFORM_NAME "stm32f072")
        set(LOCAL_GENERIC_PLATFORM_DIR "${LOCAL_GENERIC_PLATFORMS_DIR}/cortex_m0")
        set(LOCAL_GENERIC_PLATFORM_NAME "cortex_m0")
    elseif("${TARGET_PLATFORM}" STREQUAL "STM32F103")
        set(LOCAL_PLATFORM_DIR "${LOCAL_PLATFORMS_DIR}/stm32f103")
        set(LOCAL_PLATFORM_NAME "stm32f103")
        set(LOCAL_GENERIC_PLATFORM_DIR "${LOCAL_GENERIC_PLATFORMS_DIR}/cortex_m3")
        set(LOCAL_GENERIC_PLATFORM_NAME "cortex_m3")
    else()
        message(FATAL_ERROR "Unknown target platform defined (${TARGET_PLATFORM}).")
    endif()
    
    file(GLOB files "${LOCAL_PLATFORM_DIR}/*.hpp")
    foreach(file ${files})
        get_filename_component(FILE_NAME "${file}" NAME)
        write_file(
            "${MODULE_TARGET_PLATFORM_DIR}/${FILE_NAME}"
            "#pragma once\n\n"
            "#include <mtl/hw/devices/${LOCAL_PLATFORM_NAME}/${FILE_NAME}>"
        )
        list(APPEND SOURCE_LIST "${MODULE_TARGET_PLATFORM_DIR}/${FILE_NAME}")
    endforeach()

    file(GLOB files "${LOCAL_GENERIC_PLATFORM_DIR}/*.hpp")
    foreach(file ${files})
        get_filename_component(FILE_NAME "${file}" NAME)
        write_file(
            "${MODULE_TARGET_PLATFORM_DIR}/${FILE_NAME}"
            "#pragma once\n\n"
            "#include <mtl/hw/generic/${LOCAL_GENERIC_PLATFORM_NAME}/${FILE_NAME}>"
        )
        list(APPEND SOURCE_LIST "${MODULE_TARGET_PLATFORM_DIR}/${FILE_NAME}")
    endforeach()
    
    list(APPEND INCLUDE_DIRS "${MODULE_TARGET_PLATFORM_DIR}")
endif()

target_sources(${LIBRARY} INTERFACE ${SOURCE_LIST})

include(GNUInstallDirs)
target_include_directories(
    ${LIBRARY} INTERFACE
    $<BUILD_INTERFACE:${INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# target_link_libraries(${LIBRARY} INTERFACE mtl::algorithm)

# Configure testing project.
if(USE_TESTS)
    enable_testing()
    set(BINARY ${PROJECT_NAME}_test)

    set(TESTS_SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/main.test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/device.test.cpp)
    add_executable(${BINARY} ${TESTS_SOURCE_LIST})

    target_link_libraries(${BINARY} PRIVATE CONAN_PKG::catch2 mtl::${LIBRARY})

    add_test(NAME ${BINARY}
        COMMAND ${BINARY} -r junit)
endif()
