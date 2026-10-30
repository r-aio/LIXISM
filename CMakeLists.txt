cmake_minimum_required(VERSION 3.16)
project(LIXISM_Core C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O3 -fno-strict-aliasing")

include_directories(dcripts include)

add_executable(lixism_simulation src/main_simulation.c)
