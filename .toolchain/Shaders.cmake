macro(compile_shaders interface)
    if (ENABLE_SHADERS)
        find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)

        foreach(SHADER ${XRN_FRAGMENTS})
            get_filename_component(FILE_NAME ${SHADER} NAME)
            set(SPIRV "${XRN_FRAGMENTS_DIR}/${FILE_NAME}.spv")
            add_custom_command(
                OUTPUT ${SPIRV}
                COMMAND glslc -fshader-stage="fragment" ${SHADER} -o ${SPIRV}
                DEPENDS ${SHADER}
                COMMENT "Compiling ${SHADER}"
            )
            list(APPEND SPIRV_BINARY_FILES ${SPIRV})
        endforeach(SHADER)

        foreach(SHADER ${XRN_VERTEXES})
            get_filename_component(FILE_NAME ${SHADER} NAME)
            set(SPIRV "${XRN_VERTEXES_DIR}/${FILE_NAME}.spv")
            add_custom_command(
                OUTPUT ${SPIRV}
                COMMAND glslc -fshader-stage="vertex" ${SHADER} -o ${SPIRV}
                DEPENDS ${SHADER}
                COMMENT "Compiling ${SHADER}"
            )
            list(APPEND SPIRV_BINARY_FILES ${SPIRV})
        endforeach(SHADER)

        add_custom_target(shaders ALL DEPENDS ${SPIRV_BINARY_FILES})
    endif ()
endmacro()
