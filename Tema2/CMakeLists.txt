# CMake version
cmake_minimum_required(VERSION 3.0)

set(myproject "temaIEP")

# Project name
project(${myproject})

# Specify the required C++ standard
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)


# Define the subdirectory     
add_subdirectory(src)
