cmake_minimum_required(VERSION 3.26.0)

project(gvm VERSION 0.0.1 LANGUAGES C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTING "Build tests" ON)

find_package(elfio CONFIG REQUIRED)
find_package(glog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
file(GLOB_RECURSE gvm_source "src/*.cpp")
add_library(gvm ${gvm_source})
target_include_directories(gvm PUBLIC include)
target_link_libraries(
    gvm PRIVATE 
    elfio::elfio 
    glog::glog 
    fmt::fmt-header-only
)

if(BUILD_TESTING)
    file(GLOB_RECURSE gvm_test "test/*.cpp")
    add_executable(gvm_test ${gvm_test})
    find_package(GTest CONFIG REQUIRED)
    target_link_libraries(gvm_test gvm GTest::gtest GTest::gtest_main)
endif()