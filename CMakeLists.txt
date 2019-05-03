cmake_minimum_required(VERSION 3.13)
project(Adaptive_Poisson_Disk_Sampling)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Adaptive_Poisson_Disk_Sampling
        src/main.cpp
        )
