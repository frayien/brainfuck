cmake_minimum_required(VERSION 3.0.0)
project(brainfuckCompiler VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -O3") 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

include_directories(include)


file(
    GLOB_RECURSE
    SRCS
    src/*
)

file(
    GLOB_RECURSE 
    HEADERS 
    include/*
)

add_executable(brainfuckCompiler ${HEADERS} ${SRCS})

target_link_libraries(
    brainfuckCompiler
)