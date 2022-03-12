cmake_minimum_required(VERSION 3.22)
project(opengl-by-glfw)

# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

add_definitions("-std=c++11")

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
                TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup(TARGETS)
conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE ..
                    BUILD missing
                    REMOTE conancenter
                    SETTINGS ${settings}
                    GENERATOR cmake;cmake_find_package)

find_package(OpenGL REQUIRED)

add_executable(opengl-by-glfw src/main.cpp src/program.cpp src/box.cpp)

target_link_libraries(opengl-by-glfw OpenGL::GL CONAN_PKG::glfw CONAN_PKG::glm)
