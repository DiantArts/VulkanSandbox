macro(enable_tests)
    if (ENABLE_TESTING)
        set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
        enable_testing()

        # =========================================================================
        # Unit tests
        # =========================================================================

        if (ENABLE_UNIT_TESTING)
            message(STATUS "Building tests")
            add_subdirectory(${XRN_TESTS_DIR}/unit)
        endif ()



        # =========================================================================
        # Benchmarks
        # =========================================================================

        if (ENABLE_BENCHMARKS)
            message(STATUS "Building benchmarks")
            message(WARNING "Benchmarks not supported yet. Ignored")
        endif ()



        # =========================================================================
        # Fuzz tests
        # =========================================================================


        if (ENABLE_FUZZ_TESTING)
            message(STATUS "Building fuzzing tests")
            message(WARNING "Fuzz tests not supported yet. Ignored")
            add_subdirectory(${XRN_TESTS_DIR}/fuzz)
        endif ()
    endif ()

endmacro()
