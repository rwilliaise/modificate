
find_package(glfw3)
find_package(assimp)

if (NOT glfw3_FOUND)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
    set(GLFW_INSTALL OFF CACHE BOOL "")

    fetchcontent_declare(glfw
        GIT_REPOSITORY  https://github.com/glfw/glfw.git
        GIT_TAG         3.3.8
    )

    fetchcontent_makeavailable(glfw)
endif()

if (NOT assimp_FOUND)
    message(STATUS "Did not find assimp, building from source. This will take a while.")
    set(ASSIMP_INSTALL OFF CACHE BOOL "")
    set(ASSIMP_BUILD_ASSIMP_VIEW OFF CACHE BOOL "")

    fetchcontent_declare(assimp
        GIT_REPOSITORY  https://github.com/assimp/assimp
        GIT_TAG         v5.2.5
    )

    fetchcontent_makeavailable(assimp)
endif()

set(GLAD_LOCATION ${CMAKE_SOURCE_DIR}/thirdparty/glad)

add_executable(modificate_client
    client.c
    window.c
    camera.c
    chunk.c
    atlas.c
    stb_image.c
    ${GLAD_LOCATION}/src/gl.c
)
target_link_libraries(modificate_client PRIVATE glfw modificate_shared
    assimp::assimp)
target_link_libraries(modificate_interface INTERFACE glfw assimp::assimp)
target_include_directories(modificate_client SYSTEM PRIVATE
    ${GLAD_LOCATION}/include include)

set_target_properties(modificate_client PROPERTIES
    MACOSX_BUNDLE ON
    MACOSX_FRAMEWORK_IDENTIFIER com.rwilliaise.modificate)
