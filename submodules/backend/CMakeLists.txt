file(GLOB_RECURSE backend_sources "src/*.cpp")
add_library(backend ${backend_sources})
target_include_directories(backend PUBLIC include)