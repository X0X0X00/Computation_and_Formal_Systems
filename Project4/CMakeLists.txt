cmake_minimum_required(VERSION 3.20)
project(Proj4 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Werror")


add_executable(Proj4
        main.c
        snop.c
        pm.c
        pda.c
        pd.c
        psh.c
        pmda.c
)
