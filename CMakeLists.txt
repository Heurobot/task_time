cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)


include_directories(inc) # Include the directory where your source files are located

file(GLOB_RECURSE SOURCES "src/*.cpp")# Recursively find all .cpp files in the code directory

add_executable(task_time ${SOURCES})