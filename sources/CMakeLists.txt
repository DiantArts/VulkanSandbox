if (CMAKE_CURRENT_LIST_DIR MATCHES "-src/sources$")
    include(${XRN_BUILD_DIR}/_deps/${XRN_BIN_NAME}/conanbuildinfo.cmake)
else ()
    include(${XRN_BUILD_DIR}/conanbuildinfo.cmake)
endif ()
conan_basic_setup(TARGETS)

include(CMakeFindDependencyMacro)
foreach(library IN LISTS XRN_LIBRARIES_REQUIREMENTS)
    find_dependency(${library} REQUIRED)
endforeach()

get_filename_component(XRN_CLIENT_MAIN ${XRN_SOURCES_DIR}/Client/main.cpp REALPATH)
get_filename_component(XRN_SERVER_MAIN ${XRN_SOURCES_DIR}/Server/main.cpp REALPATH)
list(REMOVE_ITEM XRN_SOURCES "${XRN_CLIENT_MAIN}")
list(REMOVE_ITEM XRN_SOURCES "${XRN_SERVER_MAIN}")


if (COMPILE_SERVER)
    add_library(XRN_${XRN_BIN_NAME}_BIN_OBJECTS_SERVER OBJECT ${XRN_SERVER_MAIN} ${XRN_SOURCES} ${XRN_FRAGMENT} ${XRN_VERTEX} ${XRN_HEADERS})

    if (ENABLE_PCH)
        target_precompile_headers(
            XRN_${XRN_BIN_NAME}_BIN_OBJECTS_SERVER
            PRIVATE
                <pch.hpp>
        )
    endif ()

    if (ENABLE_BINARY)
        target_link_libraries(
            XRN_${XRN_BIN_NAME}_BIN_OBJECTS_SERVER
            PUBLIC
                ${XRN_BIN_NAME}_project_options
                ${XRN_BIN_NAME}_project_warnings
                ${XRN_BIN_NAME}_project_dependencies
                ${XRN_LIBRARIES_DEPENDENCIES}
        )
        add_executable(${XRN_BIN_NAME}_server $<TARGET_OBJECTS:XRN_${XRN_BIN_NAME}_BIN_OBJECTS_SERVER>)

        target_link_libraries(
            ${XRN_BIN_NAME}_server
            PRIVATE
                XRN_${XRN_BIN_NAME}_BIN_OBJECTS_SERVER
        )
    endif ()

    set_property(TARGET XRN_${XRN_BIN_NAME}_BIN_OBJECTS_SERVER PROPERTY POSITION_INDEPENDENT_CODE 1)
    if (ENABLE_STATIC_LIBRARY)
        add_library(${XRN_BIN_NAME}_static STATIC $<TARGET_OBJECTS:XRN_${XRN_BIN_NAME}_BIN_OBJECTS_SERVER>)
        set_target_properties(${XRN_BIN_NAME}_static PROPERTIES OUTPUT_NAME ${XRN_BIN_NAME})
    endif ()

    if (ENABLE_SHARED_LIBRARY)
        add_library(${XRN_BIN_NAME}_shared SHARED $<TARGET_OBJECTS:XRN_${XRN_BIN_NAME}_BIN_OBJECTS_SERVER>)
        set_target_properties(${XRN_BIN_NAME}_shared PROPERTIES OUTPUT_NAME ${XRN_BIN_NAME})
    endif ()
endif ()



add_library(XRN_${XRN_BIN_NAME}_BIN_OBJECTS_CLIENT OBJECT ${XRN_CLIENT_MAIN} ${XRN_SOURCES} ${XRN_FRAGMENT} ${XRN_VERTEX} ${XRN_HEADERS})

if (ENABLE_PCH)
    target_precompile_headers(
        XRN_${XRN_BIN_NAME}_BIN_OBJECTS_CLIENT
        PRIVATE
            <pch.hpp>
    )
endif ()

if (ENABLE_BINARY)
    target_link_libraries(
        XRN_${XRN_BIN_NAME}_BIN_OBJECTS_CLIENT
        PUBLIC
            ${XRN_BIN_NAME}_project_options
            ${XRN_BIN_NAME}_project_warnings
            ${XRN_BIN_NAME}_project_dependencies
            ${XRN_LIBRARIES_DEPENDENCIES}
    )
    add_executable(${XRN_BIN_NAME}_client $<TARGET_OBJECTS:XRN_${XRN_BIN_NAME}_BIN_OBJECTS_CLIENT>)

    target_link_libraries(
        ${XRN_BIN_NAME}_client
        PRIVATE
            XRN_${XRN_BIN_NAME}_BIN_OBJECTS_CLIENT
    )
endif ()

set_property(TARGET XRN_${XRN_BIN_NAME}_BIN_OBJECTS_CLIENT PROPERTY POSITION_INDEPENDENT_CODE 1)
if (ENABLE_STATIC_LIBRARY)
    add_library(${XRN_BIN_NAME}_static STATIC $<TARGET_OBJECTS:XRN_${XRN_BIN_NAME}_BIN_OBJECTS_CLIENT>)
    set_target_properties(${XRN_BIN_NAME}_static PROPERTIES OUTPUT_NAME ${XRN_BIN_NAME})
endif ()

if (ENABLE_SHARED_LIBRARY)
    add_library(${XRN_BIN_NAME}_shared SHARED $<TARGET_OBJECTS:XRN_${XRN_BIN_NAME}_BIN_OBJECTS_CLIENT>)
    set_target_properties(${XRN_BIN_NAME}_shared PROPERTIES OUTPUT_NAME ${XRN_BIN_NAME})
endif ()



foreach(library IN LISTS XRN_LIBRARIES_HEADERS)
    include_directories(
        ${${library}_INCLUDE_DIRS}
    )
endforeach()
