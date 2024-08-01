file(GLOB_RECURSE GDBSTUB_SOURCES src/*.c)
add_library(gdbstub STATIC ${GDBSTUB_SOURCES})
target_include_directories(gdbstub PUBLIC include)
target_compile_definitions(gdbstub PRIVATE GDBSTUB_ARCH_MOCK GDBSTUB_IMPLEMENTATION)