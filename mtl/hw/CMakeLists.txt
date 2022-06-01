cmake_minimum_required(VERSION 3.9)
project(hw)

set(CMAKE_CXX_STANDARD 17)

# Configure library.
set(LIBRARY ${PROJECT_NAME})

add_library(${LIBRARY} INTERFACE)
add_library(mtl::${LIBRARY} ALIAS ${LIBRARY})

set(INCLUDE_DIRS ${CMAKE_SOURCE_DIR})

set(SOURCE_LIST
    "${CMAKE_CURRENT_SOURCE_DIR}/device.hpp")

if(DEFINED TARGET_PLATFORM)
    set(LOCAL_PLATFORMS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/devices")
    
    if(DEFINED TARGET_PLATFORM_DIR)
        set(MODULE_TARGET_PLATFORM_DIR "${TARGET_PLATFORM_DIR}/mtl/hw/device")
        if(EXISTS ${MODULE_TARGET_PLATFORM_DIR})
            file(REMOVE_RECURSE ${MODULE_TARGET_PLATFORM_DIR})
        endif()
        file(MAKE_DIRECTORY "${MODULE_TARGET_PLATFORM_DIR}")
    else()
        message(FATAL_ERROR "Directory for platform specific code must be defined.")
    endif()

    message("${TARGET_PLATFORM}")
    if("${TARGET_PLATFORM}" STREQUAL "STM32F072")
        set(LOCAL_PLATFORM_DIR "${LOCAL_PLATFORMS_DIR}/stm32f072")
    elseif("${TARGET_PLATFORM}" STREQUAL "STM32F103")
        set(LOCAL_PLATFORM_DIR "${LOCAL_PLATFORMS_DIR}/stm32f103")
    else()
        message(FATAL_ERROR "Unknown target platform defined (${TARGET_PLATFORM}).")
    endif()
    
    file(GLOB_RECURSE FLS "${LOCAL_PLATFORM_DIR}/*.*")
    file(COPY "${LOCAL_PLATFORM_DIR}/" DESTINATION ${MODULE_TARGET_PLATFORM_DIR})
    
    list(APPEND INCLUDE_DIRS "${MODULE_TARGET_PLATFORM_DIR}")
endif()

target_sources(${LIBRARY} INTERFACE ${SOURCE_LIST})

include(GNUInstallDirs)
target_include_directories(
    ${LIBRARY} INTERFACE
    $<BUILD_INTERFACE:${INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(${LIBRARY} INTERFACE mtl::algorithm)

# Configure testing project.
enable_testing()
set(BINARY ${PROJECT_NAME}_test)

set(TESTS_SOURCE_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/main.test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/device.test.cpp)
add_executable(${BINARY} ${TESTS_SOURCE_LIST})

target_link_libraries(${BINARY} PRIVATE CONAN_PKG::catch2 mtl::${LIBRARY})

add_test(NAME ${BINARY}
    COMMAND ${BINARY} -r junit)
