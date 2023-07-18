cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(ExternalProject)
include(FetchContent)

project(modificate
    LANGUAGES C
    VERSION 0.1.0
)

find_program(MAKE_EXE
    NAMES gmake mingw32-make make
    NAMES_PER_DIR
    DOC "GNU Make"
)

add_compile_definitions(
    MODIFICATE_VERSION="${CMAKE_PROJECT_VERSION}"
    MODIFICATE_VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR}
    MODIFICATE_VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR}
    MODIFICATE_VERSION_PATCH=${CMAKE_PROJECT_VERSION_PATCH}
)
add_subdirectory(client)
add_subdirectory(shared)
add_subdirectory(server)

