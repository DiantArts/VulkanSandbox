# =========================================================================
# setup
# =========================================================================

# basic tests
set(XRN_BTESTS_BIN xrnTests)
set(XRN_BTESTS_DIR basic)

# constexpr tests
set(XRN_CTESTS_BIN xrnConstexprTests)
set(XRN_CTESTS_DIR constexpr)

# relaxed constexpr tests
set(XRN_RCTESTS_BIN xrnRelaxedConstexprTests)

find_package(Catch2 REQUIRED)
include(CTest)
include(Catch)

include(ProcessorCount)
ProcessorCount(XRN_NPROC)
if (NOT XRN_NPROC EQUAL 0)
    set(CTEST_BUILD_FLAGS -j${XRN_NPROC})
    set(ctest_test_args ${ctest_test_args} PARALLEL_LEVEL ${XRN_NPROC})
endif ()


# auto-runners
if (RUN_UNIT_TESTS)
    add_custom_target(tests_run ALL DEPENDS ${XRN_BTESTS_BIN} ${XRN_CTESTS_BIN} ${XRN_RCTESTS_BIN})
    add_custom_command(
        TARGET tests_run
        COMMENT "Run tests..."
        POST_BUILD
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ctest -C $<CONFIGURATION> --output-on-failures
    )
endif ()



# =========================================================================
# main of tests
# =========================================================================

# Define binary
add_library(test_configs OBJECT main.cpp ${XRN_SOURCES})
target_link_libraries(
    test_configs
    PRIVATE
        project_dependencies
)
target_link_libraries(
    test_configs
    PUBLIC
        project_options
        project_warnings
        Catch2::Catch2
)
if (ENABLE_COVERAGE)
    target_compile_options(test_configs PRIVATE -O0 -g3 -fprofile-arcs -ftest-coverage -fPIC --coverage -fno-inline -fno-inline-small-functions -fno-default-inline)
    target_link_libraries(test_configs PRIVATE --coverage)
endif ()



# =========================================================================
# basic tests
# =========================================================================

file(GLOB_RECURSE XRN_TESTS_SRC ${XRN_BTESTS_DIR}/*.cpp ${XRN_BTESTS_DIR}/*.cxx)

add_executable(${XRN_BTESTS_BIN} ${XRN_TESTS_SRC})
target_link_libraries(${XRN_BTESTS_BIN} PRIVATE test_configs)
# automatically discover tests that are defined in catch based test files you can modify the tests.
catch_discover_tests(
    ${XRN_BTESTS_BIN}
    TEST_PREFIX "tests."
    REPORTER xml
    OUTPUT_DIR .
    OUTPUT_PREFIX "tests."
    OUTPUT_SUFFIX .xml
)



# =========================================================================
# constexpr tests
# =========================================================================

file(GLOB_RECURSE XRN_CTESTS_SRC ${XRN_CTESTS_DIR}/*.cpp ${XRN_CTESTS_DIR}/*.cxx)
add_library(XRN_TESTS_OBJECTS OBJECT ${XRN_CTESTS_SRC})
target_link_libraries(XRN_TESTS_OBJECTS PRIVATE test_configs)

# normal constexpr
add_executable(${XRN_CTESTS_BIN} $<TARGET_OBJECTS:XRN_TESTS_OBJECTS>)
target_link_libraries(${XRN_CTESTS_BIN} PRIVATE test_configs)
catch_discover_tests(
    ${XRN_CTESTS_BIN}
    TEST_PREFIX "ctests."
    REPORTER xml
    OUTPUT_DIR .
    OUTPUT_PREFIX "ctests."
    OUTPUT_SUFFIX .xml
)

# relaxed constexpr: Disable the constexpr portion of the test, and build again this allows us to have an
# executable that we can debug when things go wrong with the constexpr testing
add_executable(${XRN_RCTESTS_BIN} $<TARGET_OBJECTS:XRN_TESTS_OBJECTS>)
target_link_libraries(${XRN_RCTESTS_BIN} PRIVATE test_configs)
target_compile_definitions(${XRN_RCTESTS_BIN} PRIVATE -DCATCH_CONFIG_RUNTIME_STATIC_REQUIRE)
catch_discover_tests(
    ${XRN_RCTESTS_BIN}
    TEST_PREFIX "rctests."
    REPORTER xml
    OUTPUT_DIR .
    OUTPUT_PREFIX "rctests."
    OUTPUT_SUFFIX .xml
)



# =========================================================================
# functionnal tests
# =========================================================================

# Provide a simple smoke test to make sure that the CLI works and can display a --help message
# add_test(NAME cli.has_help COMMAND intro --help)

# Provide a test to verify that the version being reported from the application
# matches the version given to CMake. This will be important once you package
# your program. Real world shows that this is the kind of simple mistake that is easy
# to make, but also easy to test for.
# add_test(NAME cli.version_matches COMMAND intro --version)
# set_tests_properties(cli.version_matches PROPERTIES PASS_REGULAR_EXPRESSION "${PROJECT_VERSION}")
