cmake_minimum_required(VERSION 3.30)

project(gvm VERSION 0.0.1 LANGUAGES C CXX ASM)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTING "Build tests" ON)

add_subdirectory(submodules/core)
add_subdirectory(submodules/common)
add_subdirectory(submodules/gdbstub)