cmake_minimum_required(VERSION 3.24)
project(SimpleDB C)

set(CMAKE_C_STANDARD 11)

add_executable(practice main.c user.h user.c db.c db.h)
