# TODO: GDB support is not yet implemented in this project.
find_package(Boost REQUIRED COMPONENTS circular_buffer)
file(GLOB_RECURSE GDBSTUB_SOURCES "src/*.cpp")
add_library(gdbstub STATIC ${GDBSTUB_SOURCES})
target_include_directories(gdbstub PUBLIC include)
target_link_libraries(gdbstub PUBLIC Boost::circular_buffer common)

if(BUILD_TESTING)
    find_package(GTest CONFIG REQUIRED)
    file(GLOB_RECURSE GDBSTUB_TEST_SOURCES "test/*.cpp")
    add_executable(gdbstub_test ${GDBSTUB_TEST_SOURCES})
    target_link_libraries(gdbstub_test gdbstub GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
endif()