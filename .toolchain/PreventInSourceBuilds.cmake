function(prevent_in_source_builds)

    # =========================================================================
    # In Source builds
    # =========================================================================

    # disallow in-source builds
    if("${XRN_ROOT_DIR}" STREQUAL "${XRN_BUILD_DIR}")
        message(
            WARNING
            "in-source builds are disabled, yet rootdir:${XRN_ROOT_DIR} and builddir:${XRN_BUILD_DIR} are identical"
        )
        message("Please create a separate build directory and run cmake from there")
        message(FATAL_ERROR "Quitting configuration")
    endif()



    # =========================================================================
    # In Toolchain builds
    # =========================================================================

    # disallow in-source builds
    if("${toolchaindir}" STREQUAL "${XRN_BUILD_DIR}")
        message(
            WARNING
            "in-toolchain builds are disabled, yet toolchaindir:${toolchaindir} and builddir:${XRN_BUILD_DIR} are identical"
        )
        message("Please create a separate build directory and run cmake from there")
        message(FATAL_ERROR "Quitting configuration")
    endif()

endfunction()
