cmake_minimum_required(VERSION 3.28)
project(Web_Server_in_Pure_C C)

set(CMAKE_C_STANDARD 11)

add_executable(Web_Server_in_Pure_C
        src/server.c
        src/main.c
        include/server.h
        src/client.c
)

add_executable(showip
        src/showip.c
)
