cmake_minimum_required(VERSION 3.26)
project(client_server C)

set(CMAKE_C_STANDARD 23)

add_executable(client_server server.c
        lib.c
        lib.h
        client.c)
