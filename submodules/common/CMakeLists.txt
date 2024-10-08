file(GLOB_RECURSE common_src "src/*.cpp")
file(GLOB_RECURSE common_test_src "test/*.cpp")

find_package(fmt CONFIG REQUIRED)
add_library(common ${common_src})
target_include_directories(common PUBLIC include)
target_link_libraries(common PUBLIC fmt::fmt)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(common PUBLIC GVM_DEBUG)
endif()

if(BUILD_TESTING)
    add_executable(common_test ${common_test_src})
    find_package(GTest CONFIG REQUIRED)
    target_link_libraries(common_test common GTest::gtest GTest::gtest_main)
endif()