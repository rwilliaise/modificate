cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(ExternalProject)
include(FetchContent)

project(modificate C)

find_program(MAKE_EXE
    NAMES gmake mingw32-make make
    NAMES_PER_DIR
    DOC "GNU Make"
)

add_subdirectory(client)
add_subdirectory(shared)
add_subdirectory(server)

