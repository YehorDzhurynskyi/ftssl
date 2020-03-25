cmake_minimum_required(VERSION 3.1)

project(ft_ssl)

add_executable(ref_md5
    src/ref_md5.c
)

add_executable(ref_sha256
        src/ref_sha256.cpp
)

set_target_properties(ref_sha256
    PROPERTIES
        LINKER_LANGUAGE "CXX"
        CXX_STANDARD    17
)

add_executable(ft_ssl
    src/main.c
    src/buffer.h
    src/buffer.c
    src/error.h
    src/error.c
    src/request.h
    src/request.c
    src/command.h
    src/command.c
    src/provider.c

    src/md5/md5.h
    src/md5/md5.c
    src/md5/md5_ctx.c
    src/md5/md5_internal.h
    src/md5/md5_funcs.c

    src/sha256/sha256.h
    src/sha256/sha256.c
    src/sha256/sha256_ctx.c
    src/sha256/sha256_internal.h

    src/sha224/sha224.h
    src/sha224/sha224.c

    src/sha512/sha512.h
    src/sha512/sha512.c
    src/sha512/sha512_ctx.c
    src/sha512/sha512_internal.h

    src/sha384/sha384.h
    src/sha384/sha384.c
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
