macro(set_standard_project_settings interface language_version)
    SET(CMAKE_CXX_STANDARD ${language_version})
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    if (ENABLE_OUTPUT_DIR)
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${XRN_OUTPUT_DIR})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${XRN_OUTPUT_DIR})
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${XRN_OUTPUT_DIR})
    endif ()

    # Set a default build type if none was specified
    if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
        message(STATUS "Built type set to RelWithDebInfo (default option)")
        set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
        # Set the possible values of build type for cmake
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
    endif ()

    # Generate a compile_commands.json to make it easier to work with clang based tools
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    # Enable IterpPocedural Optimization (LTO: Link Time Optimization) if needed
    if (ENABLE_IPO)
        include(ProcessorCount)
        ProcessorCount(XRN_NPROC)
        if (NOT XRN_NPROC EQUAL 0)
            set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_JOBS ${XRN_NPROC})
        endif ()

        include(CheckIPOSupported)
        check_ipo_supported(RESULT isIpoSupported OUTPUT output)
        if (isIpoSupported)
            message(STATUS "IPO enabled (${XRN_NPROC} procs)")
            set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
        else ()
            message(WARNING "IPO is not supported: ${output}")
        endif ()
    endif ()
endmacro()
