cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

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

fetchcontent_declare(cglm
    GIT_REPOSITORY  https://github.com/recp/cglm
    GIT_TAG         v0.9.0
)

fetchcontent_makeavailable(cglm)
find_package(Threads REQUIRED)
link_libraries(Threads::Threads cglm m)

add_compile_definitions(
    MODIFICATE_VERSION="${CMAKE_PROJECT_VERSION}"
    MODIFICATE_VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR}
    MODIFICATE_VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR}
    MODIFICATE_VERSION_PATCH=${CMAKE_PROJECT_VERSION_PATCH}
    $<$<BOOL:${CMAKE_USE_PTHREADS_INIT}>:USE_PTHREADS>
    $<$<BOOL:${CMAKE_USE_WIN32_THREADS_INIT}>:USE_WIN32_THREADS>
)
add_subdirectory(client)
add_subdirectory(shared)
add_subdirectory(server)

