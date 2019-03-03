cmake_minimum_required(VERSION 3.12)
project(Wechat C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(user_test
        src/user_test.c
        src/user.c
        src/user.h)
