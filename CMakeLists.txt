cmake_minimum_required(VERSION 3.28)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

project(OpenGL-Project VERSION 1.0)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_subdirectory(src)