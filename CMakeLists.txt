cmake_minimum_required(VERSION 3.1)

project(ft_ssl)

add_executable(ft_ssl
    src/main.c
    src/buffer.h
    src/buffer.c
    src/error.h
    src/error.c
    src/request.h
    src/request.c
    src/provider.c

    src/md5/md5.h
    src/md5/md5.c
    src/md5/md5_internal.h
    src/md5/md5_funcs.c
    src/md5/md5_rounds.c
)

target_include_directories(ft_ssl
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src
)

set_target_properties(ft_ssl
    PROPERTIES
        LINKER_LANGUAGE "C"
)

if (UNIX)
    message(STATUS "linking libft")

    add_subdirectory(libft)

    target_link_libraries(ft_ssl
        PUBLIC
            ft
    )

    target_compile_options(ft_ssl
        PRIVATE
            -Wall -Werror -Wunused
    )
endif ()
