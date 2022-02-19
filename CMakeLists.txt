cmake_minimum_required(VERSION 3.22)
project(opengl-by-glfw)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(OpenGL REQUIRED)

add_executable(opengl-by-glfw src/main.cpp)
