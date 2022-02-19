cmake_minimum_required(VERSION 3.0)
project(opengl-by-glfw)

set(CMAKE_TOOLCHAIN_FILE "/Users/eita/build/vcpkg/scripts/buildsystems/vcpkg.cmake")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(OpenGL REQUIRED)

add_executable(opengl-by-glfw src/main.cpp)
