cmake_minimum_required(VERSION 3.25)
project(Project2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project2 main.cpp include/CacheSim.h lib/CacheSim.cpp)
