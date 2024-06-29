file(GLOB_RECURSE core_sources "src/*.cpp")
file(GLOB_RECURSE core_test_sources "test/*.cpp")

find_package(fmt CONFIG REQUIRED)
add_library(core ${core_sources})
target_include_directories(core PUBLIC include)
target_link_libraries(core fmt::fmt)


if(BUILD_TESTING)
    find_package(GTest CONFIG REQUIRED)
    add_executable(core_test ${core_test_sources})
    target_link_libraries(core_test core GTest::gtest GTest::gtest_main)
endif()