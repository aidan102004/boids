cmake_minimum_required(VERSION 3.16)
project(boids CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)

add_executable(boids
    src/main.cpp
    src/renderer.h
)
target_link_libraries(boids PRIVATE SDL2::SDL2)