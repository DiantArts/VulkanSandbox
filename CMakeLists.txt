cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

# =========================================================================
# Configuration
# =========================================================================

# project
project(CMakeSandbox LANGUAGES CXX)
set(XRN_BIN_NAME xrn)
set(XRN_CXX_VERSION 23)

# dependencies
set(XRN_LIBS_REQUIRED glfw/3.3.7 entt/3.10.1 fmt/8.1.1)
set(XRN_LIBRARIES_REQUIREMENTS Vulkan glfw3 EnTT fmt Threads) # find_package
set(XRN_LIBRARIES_DEPENDENCY Vulkan::Vulkan glfw::glfw EnTT::EnTT fmt::fmt Threads::Threads) # target_link_libraries
set(XRN_LIBRARIES_HEADERS glfw3 EnTT fmt) # include_directories(${library}_INCLUDE_DIRS)

set(SPDLOG_BUILD_SHARED OFF)
set(SPDLOG_FMT_EXTERNAL ON)
set(SPDLOG_BUILD_EXAMPLE OFF)
set(SPDLOG_BUILD_TESTS OFF)

# paths
set(XRN_TOOLCHAIN_DIR "${CMAKE_SOURCE_DIR}/.toolchain")
set(XRN_TOOLCHAIN_DETAILS_DIR "${XRN_TOOLCHAIN_DIR}/.details")
set(XRN_SOURCES_DIR "sources")
set(XRN_TESTS_DIR "tests")
set(XRN_EXTERNAL_DIR "externals")
set(XRN_OUTPUT_DIR "binaries")

set(XRN_SHADERS_DIR "shaders")
set(XRN_FRAGMENTS_DIR "Fragment")
set(XRN_VERTEXES_DIR "Vertex")

# testing
option(ENABLE_TESTING "Enable testing" OFF)
option(ENABLE_UNIT_TESTING "Build unit tests" OFF)
option(RUN_UNIT_TESTS "Run the tests at the end of their compilation" OFF)
option(ENABLE_BENCHMARKS "Build benchmarks" OFF)
option(ENABLE_FUZZ_TESTING "Build fuzzing tests" OFF)

# dev mode
option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" OFF)
option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)

# static analysis
option(ENABLE_STATIC_ANALYSIS "Enable static analysis" OFF)
option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)

# sanatizer
option(ENABLE_SANITIZERS "Allow to enable a sanitizer, checks if the compiler supports sanitizers" OFF)
option(ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ON)
option(ENABLE_SANITIZER_LEAK "Enable leak sanitizer" ON)
option(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR "Enable undefined behavior sanitizer" ON)
option(ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
option(ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)

# compilations
option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
option(ENABLE_C++20_COROUTINES "Enable coroutines supports" OFF)
option(ENABLE_SHADERS "Compiles GLSL shaders to SPV" ON)

# optimization
option(ENABLE_IPO "Enable IterpPocedural Optimization (Link Time Optimization)" ON)
option(ENABLE_CACHE "Enable cache if available" ON)
option(ENABLE_STD_PCH "Enable Precompiled Headers of the STD library" ON)
option(ENABLE_PCH "Enable personal Precompiled Headers (<pch.hpp>)" ON)

# others
option(ENABLE_UPDATE_CONAN "Enable updates of the <conan.cmake> file each run" OFF)
option(ENABLE_DOCUMENTATION "Enable doxygen doc builds of source" OFF)
option(ENABLE_CMAKE_DEBUG "Enable debug outputs of cmake's makefiles" ON)

# Binary form
option(ENABLE_OUTPUT_DIR "Puts every ouput binaries in the '${XRN_OUTPUT_DIR}' directory" OFF)
option(ENABLE_BINARY "Compile the main program as a binarry" ON)
option(ENABLE_STATIC_LIBRARY "Compile the main program as a static library" OFF)
option(ENABLE_SHARED_LIBRARY "Compile the main program as a shared library" OFF)



# =========================================================================
# Abolute paths
# =========================================================================

set(XRN_ROOT_DIR_RELATIVE ${CMAKE_SOURCE_DIR})
set(XRN_BUILD_DIR_RELATIVE ${CMAKE_BINARY_DIR})
set(XRN_TOOLCHAIN_DIR_RELATIVE ${XRN_TOOLCHAIN_DIR})
set(XRN_TOOLCHAIN_DETAILS_DIR_RELATIVE ${XRN_TOOLCHAIN_DETAILS_DIR})
set(XRN_SOURCES_DIR_RELATIVE ${XRN_SOURCES_DIR})
set(XRN_TESTS_DIR_RELATIVE ${XRN_TESTS_DIR})
set(XRN_INCLUDE_DIRS_RELATIVE ${XRN_EXTERNAL_DIR})

set(XRN_SHADERS_DIR_RELATIVE ${XRN_SHADERS_DIR})
set(XRN_FRAGMENTS_DIR_RELATIVE ${XRN_SHADERS_DIR}/${XRN_FRAGMENTS_DIR})
set(XRN_VERTEXES_DIR_RELATIVE ${XRN_SHADERS_DIR}/${XRN_VERTEXES_DIR})

get_filename_component(XRN_ROOT_DIR ${CMAKE_SOURCE_DIR} REALPATH)
get_filename_component(XRN_BUILD_DIR ${CMAKE_BINARY_DIR} REALPATH)
get_filename_component(XRN_TOOLCHAIN_DIR ${XRN_TOOLCHAIN_DIR} REALPATH)
get_filename_component(XRN_TOOLCHAIN_DETAILS_DIR ${XRN_TOOLCHAIN_DETAILS_DIR} REALPATH)
get_filename_component(XRN_SOURCES_DIR ${XRN_SOURCES_DIR} REALPATH)
get_filename_component(XRN_TESTS_DIR ${XRN_TESTS_DIR} REALPATH)
get_filename_component(XRN_EXTERNAL_DIR ${XRN_EXTERNAL_DIR} REALPATH)
get_filename_component(XRN_OUTPUT_DIR ${XRN_BUILD_DIR}/${XRN_OUTPUT_DIR} REALPATH)

get_filename_component(XRN_SHADERS_DIR ${XRN_SHADERS_DIR} REALPATH)
get_filename_component(XRN_VERTEXES_DIR ${XRN_VERTEXES_DIR_RELATIVE} REALPATH)
get_filename_component(XRN_FRAGMENTS_DIR ${XRN_FRAGMENTS_DIR_RELATIVE} REALPATH)



# =========================================================================
# Sources
# =========================================================================

get_filename_component(XRN_MAIN ${XRN_SOURCES_DIR}/main.cpp REALPATH)
file(
    GLOB_RECURSE
    XRN_SOURCES
    ${XRN_SOURCES_DIR}/*.cpp
    ${XRN_SOURCES_DIR}/*.cxx
    ${XRN_SOURCES_DIR}/*.c
    ${XRN_SOURCES_DIR}/*.CC
    PARENT_SCOPE
)
file(
    GLOB_RECURSE
    XRN_HEADERS
    ${XRN_SOURCES_DIR}/*.hpp
    ${XRN_SOURCES_DIR}/*.hxx
    ${XRN_SOURCES_DIR}/*.h
    PARENT_SCOPE
)
file(
    GLOB_RECURSE
    XRN_FRAGMENTS
    ${XRN_FRAGMENTS_DIR}/*.glsl
    ${XRN_FRAGMENTS_DIR}/*.shader
    ${XRN_SHADERS_DIR}/*.vert
    ${XRN_SHADERS_DIR}/*.vertex
    ${XRN_SHADERS_DIR}/*.vs
    PARENT_SCOPE
)
file(
    GLOB_RECURSE
    XRN_VERTEXES
    ${XRN_VERTEXES_DIR}/*.glsl
    ${XRN_VERTEXES_DIR}/*.shader
    ${XRN_SHADERS_DIR}/*.vert
    ${XRN_SHADERS_DIR}/*.vertex
    ${XRN_SHADERS_DIR}/*.fs
    PARENT_SCOPE
)



# =========================================================================
# Setup interfaces and configurations
# =========================================================================

# debug
if (ENABLE_CMAKE_DEBUG)
    SET(CMAKE_VERBOSE_MAKEFILE TRUE)
endif ()

# generate sources list without the main
list(REMOVE_ITEM XRN_SOURCES "${XRN_MAIN}")

# includes
include_directories(${XRN_SOURCES_DIR})
include_directories(${XRN_EXTERNAL_DIR})

# interfaces
add_library(project_options INTERFACE)
add_library(project_warnings INTERFACE)
add_library(project_dependencies INTERFACE)



# =========================================================================
# Implementation
# =========================================================================

# checks the build directory if it points to the sources, aborts if it does
include(${XRN_TOOLCHAIN_DIR}/PreventInSourceBuilds.cmake)
prevent_in_source_builds()

# basic useful actions controlled by the options/
include(${XRN_TOOLCHAIN_DIR}/StandardProjectSettings.cmake)
set_standard_project_settings(project_options ${XRN_CXX_VERSION})

# cache if supported by compiler
include(${XRN_TOOLCHAIN_DIR}/Cache.cmake)
enable_cache()

# compiler warnings
include(${XRN_TOOLCHAIN_DIR}/CompilerWarnings.cmake)
set_compiler_warnings(project_warnings)

# compiler flags
include(${XRN_TOOLCHAIN_DIR}/CompilerFlags.cmake)
set_compiler_flags(project_warnings)

# sanitizer options if supported by compiler
include(${XRN_TOOLCHAIN_DIR}/Sanitizers.cmake)
enable_sanitizers(project_options)

# enable documentation
include(${XRN_TOOLCHAIN_DIR}/Documentation.cmake) # documentation configuration in the file
extract_documentation()

# allow for static analysis options
include(${XRN_TOOLCHAIN_DIR}/StaticAnalyzers.cmake) # possible to add more static analyzers in the file
run_static_analysis()

# add precompile headers
# include(${XRN_TOOLCHAIN_DIR}/PrecompiledHeaders.cmake)
# add_precompiled_headers(project_options)

# download dependencies
include(${XRN_TOOLCHAIN_DIR}/Dependencies.cmake)
download_dependencies("${XRN_LIBS_REQUIRED}") # isn't check whether the dowloaded failed or not

# compile shaders
include(${XRN_TOOLCHAIN_DIR}/Shaders.cmake)
compile_shaders(project_dependencies)

# sub projects
add_subdirectory(${XRN_SOURCES_DIR})

# tests
include(${XRN_TOOLCHAIN_DIR}/Tests.cmake)
enable_tests()
