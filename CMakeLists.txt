cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

# =========================================================================
# Configuration
# =========================================================================

# project
project(CMakeSandbox LANGUAGES CXX)
set(XRN_CXX_VERSION 23)

set(XRN_ERROR_LIMIT 10)

# dependencies
set(XRN_PERSONAL_DEPENDENCIES xrnLog xrnMeta xrnUtil) # include other xrn projects
set(XRN_LIBRARIES_REQUIRED glfw/3.3.7 entt/3.10.1 spdlog/1.10.0 asio/1.24.0)
set(XRN_LIBRARIES_REQUIREMENTS Vulkan glfw3 EnTT fmt Threads spdlog fmt asio) # find_package
set(XRN_LIBRARIES_DEPENDENCIES Vulkan::Vulkan glfw::glfw EnTT::EnTT fmt::fmt Threads::Threads CONAN_PKG::spdlog CONAN_PKG::fmt CONAN_PKG::asio) # target_link_libraries
set(XRN_LIBRARIES_HEADERS glfw3 EnTT spdlog fmt asio) # include_directories()

set(SPDLOG_BUILD_SHARED OFF)
set(SPDLOG_FMT_EXTERNAL ON)
set(SPDLOG_BUILD_EXAMPLE OFF)
set(SPDLOG_BUILD_TESTS OFF)

# paths
set(XRN_TOOLCHAIN_DIR "${CMAKE_SOURCE_DIR}/.toolchain")
set(XRN_TOOLCHAIN_DETAILS_DIR "${XRN_TOOLCHAIN_DIR}/.details")
set(XRN_SOURCES_DIR "sources")
set(XRN_EXTERNALS_DIR "externals")
set(XRN_TESTS_DIR "tests")
set(XRN_OUTPUT_DIR "binaries")

set(XRN_SHADERS_DIR "shaders")
set(XRN_FRAGMENTS_DIR "Fragment")
set(XRN_VERTEXES_DIR "Vertex")

option(COMPILE_SERVER "Compile the server instead of the client" OFF)

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
option(ENABLE_IPO "Enable IterpPocedural Optimization (Link Time Optimization)" OFF)
option(ENABLE_CACHE "Enable cache if available" ON)
option(ENABLE_PCH "Enable personal Precompiled Headers (<pch.hpp>)" OFF)

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
# xrnCMake
# =========================================================================

include(FetchContent)
FetchContent_Declare(
    _project_options
    GIT_REPOSITORY https://github.com/DiantArts/xrnCMake
    GIT_TAG        main
)
FetchContent_MakeAvailable(_project_options)

default_setup_filepaths()
default_find_files()
default_setup_vars()
default_setup_options()
default_setup_flags()
default_setup_dependencies()
default_setup_extra()



# =========================================================================
# Sub directories
# =========================================================================

# sub projects
if (ENABLE_TESTING)
    if (NOT CMAKE_CURRENT_LIST_DIR MATCHES "-src/sources$")
        enable_tests()
    endif ()
else ()
    add_subdirectory(${XRN_SOURCES_DIR})
endif ()

