cmake_minimum_required(VERSION 3.21)

option(MODIFICATE_INTERFACE_ONLY "Disable adding all targets other than modificate_interface" OFF)

set(CGLM_SHARED OFF CACHE BOOL "")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

include(InstallRequiredSystemLibraries)
include(ExternalProject)
include(FetchContent)

project(modificate
    LANGUAGES C
    VERSION 0.1.0
    DESCRIPTION "Voxel-based sandbox game"
)

fetchcontent_declare(cglm
    GIT_REPOSITORY  https://github.com/recp/cglm
    GIT_TAG         v0.9.0
)

fetchcontent_getproperties(cglm)
if(NOT cglm_POPULATED)
    fetchcontent_populate(cglm)
    add_subdirectory(${cglm_SOURCE_DIR} ${cglm_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_library(modificate_interface INTERFACE)
target_include_directories(modificate_interface INTERFACE shared/include/
    client/include/ interface/include/)
target_sources(modificate_interface INTERFACE
    interface/include/modificate/interface.h)
target_link_libraries(modificate_interface INTERFACE cglm)

set(CPACK_PACKAGE_NAME "Modificate")
set(CPACK_PACKAGE_VENDOR "rwilliaise and constituents")
set(CPACK_PACKAGE_CHECKSUM SHA256)
set(CPACK_PACKAGE_VERSION_MAJOR "${CMAKE_PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${CMAKE_PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${CMAKE_PROJECT_VERSION_PATCH}")
set(CPACK_VERBATIM_VARIABLES ON)
include(CPack)

if (NOT MODIFICATE_INTERFACE_ONLY)
    find_program(MAKE_EXE
        NAMES gmake mingw32-make make
        NAMES_PER_DIR
        DOC "GNU Make"
    )

    find_package(Threads REQUIRED)

    add_compile_definitions(
        MODIFICATE_VERSION="${CMAKE_PROJECT_VERSION}"
        MODIFICATE_VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR}
        MODIFICATE_VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR}
        MODIFICATE_VERSION_PATCH=${CMAKE_PROJECT_VERSION_PATCH}
        $<$<BOOL:${CMAKE_USE_PTHREADS_INIT}>:USE_PTHREADS>
        $<$<BOOL:${CMAKE_USE_WIN32_THREADS_INIT}>:USE_WIN32_THREADS>
    )

    add_subdirectory(mods/luajit)
    add_subdirectory(client)
    add_subdirectory(shared)
    add_subdirectory(server)
endif()

