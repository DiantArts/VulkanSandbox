# A fuzz test runs until it finds an error. This particular one is going to rely on libFuzzer.

# =========================================================================
# setup executable
# =========================================================================

set(XRN_FUZZ_BIN xrnFuzzTests)
file(GLOB_RECURSE XRN_SOURCES *.cpp *.cxx)
add_executable(${XRN_FUZZ_BIN} ${XRN_SOURCES})

# idk yet
target_compile_options(${XRN_FUZZ_BIN} PRIVATE -fsanitize=fuzzer,undefined,address)

# Allow short runs during automated testing to see if something new breaks (Default of 10 seconds)
set(FUZZ_RUNTIME 10 CACHE STRING "Number of seconds to run fuzz tests during ctest run")



# =========================================================================
# find dependencies
# =========================================================================

# Boost specific
# set(Boost_USE_STATIC_LIBS OFF)
# set(Boost_USE_MULTITHREADED ON)
# set(Boost_USE_STATIC_RUNTIME OFF)

# packages
# find_package(Boost 1.78.0 COMPONENTS)
find_package(fmt REQUIRED)
# find_package(Qt5 COMPONENTS Widgets REQUIRED)



# =========================================================================
# include dependencies
# =========================================================================

include_directories(
    # ${Boost_INCLUDE_DIRS}
    ${fmt_INCLUDE_DIRS}
    # ${Qt5Core_INCLUDE_DIRS}
    # ${Qt5Widgets_INCLUDE_DIRS}
    # ${Qt5Qml_INCLUDE_DIRS}
    # ${Qt5Quick_INCLUDE_DIRS}
    # ${Qt5QuickControls2_INCLUDE_DIRS}
)



# =========================================================================
# link dependencies
# =========================================================================

target_link_libraries(
    ${XRN_FUZZ_BIN}
    PRIVATE
        project_options
        project_warnings
        # ${Boost_LIBRARIES}
        fmt::fmt
        # Qt5::Widgets
        # Qt5::Core
        -coverage
        -fsanitize=fuzzer,undefined,address
)

add_test(NAME fuzz_tester_run COMMAND ${XRN_FUZZ_BIN} -max_total_time=${FUZZ_RUNTIME})
