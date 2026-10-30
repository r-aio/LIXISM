cmake\_minimum\_required(VERSION 3.16)
project(LIXISM\_Core C)
set(CMAKE\_C\_STANDARD 99)
set(CMAKE\_C\_STANDARD\_REQUIRED ON)
set(CMAKE\_C\_FLAGS "${CMAKE\_C\_FLAGS} -Wall -Wextra -O3") #

include\_directories(scripts include .)

add\_executable(lixism\_simulation src/main\_simulation.c)