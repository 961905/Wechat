cmake_minimum_required(VERSION 3.2)
project(Wechat C)

set(CMAKE_C_STANDARD 11)

include_directories(src)
include_directories(deps/list/src)

aux_source_directory(deps/list/src LIST_SRC)
MESSAGE(STATUS ${LIST_SRC})

add_executable(user_test
        src/user_test.c
        src/user.c
        src/user.h
        ${LIST_SRC})

add_executable(users_test
        ${LIST_SRC}
        src/users_test.c
        src/users.c
        src/user.c
        src/proto.h)

add_subdirectory(diary)



add_executable(server
        ${LIST_SRC}
        src/proto.c
        src/users.c
        src/user.c
        src/server.c
        src/group.c
        src/groups.c
        src/io_engine.c)
