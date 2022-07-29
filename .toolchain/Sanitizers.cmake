function(enable_sanitizers interface)
    # only linux
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")

        set(SANITIZERS "")

        if (ENABLE_SANITIZER_ADDRESS)
            list(APPEND SANITIZERS "address")
        endif ()

        if (ENABLE_SANITIZER_LEAK)
            list(APPEND SANITIZERS "leak")
        endif ()

        if (ENABLE_SANITIZER_UNDEFINED_BEHAVIOR)
            list(APPEND SANITIZERS "undefined")
        endif ()

        if (ENABLE_SANITIZER_THREAD)
            if ("address" IN_LIST SANITIZERS OR "leak" IN_LIST SANITIZERS)
                message(WARNING "Thread sanitizer does not work with Address or Leak sanitizer enabled")
            else()
                list(APPEND SANITIZERS "thread")
            endif ()
        endif ()

        if (ENABLE_SANITIZER_MEMORY AND CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
            if ("address" IN_LIST SANITIZERS OR "thread" IN_LIST SANITIZERS OR "leak" IN_LIST SANITIZERS)
                message(WARNING "Memory sanitizer does not work with Address, Thread or Leak sanitizer enabled")
            else()
                list(APPEND SANITIZERS "memory")
            endif ()
        endif ()

        list(JOIN SANITIZERS "," LIST_OF_SANITIZERS)

    else ()
        message(WARNING "Compiler does not support any sanitizer")
    endif ()

    if (ENABLE_SANITIZERS AND LIST_OF_SANITIZERS)
        if (NOT "${LIST_OF_SANITIZERS}" STREQUAL "")
            target_compile_options(${interface} INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
            target_link_libraries(${interface} INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
        endif ()
    endif ()

    # if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    # target_compile_options(${interface} INTERFACE -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer)
    # elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # target_compile_options(${interface} INTERFACE -fno-omit-frame-pointer)
    # endif ()
endfunction()
