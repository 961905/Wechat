cmake_minimum_required(VERSION 3.12)
project(Wechat C)

set(CMAKE_C_STANDARD 11)

include_directories(src)
include_directories(deps/list/src)

aux_source_directory(deps/list/src LIST_SRC)
MESSAGE(STATUS ${LIST_SRC})

add_executable(user_test
        src/user_test.c
        src/user.c
        src/user.h)

add_executable(users_test
        ${LIST_SRC}
        src/users_test.c
        src/users.c
        src/user.c)
