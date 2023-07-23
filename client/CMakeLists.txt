
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_INSTALL OFF)
set(CGLM_SHARED OFF)

fetchcontent_declare(glfw
    GIT_REPOSITORY  https://github.com/glfw/glfw.git
    GIT_TAG         3.3.8
)
fetchcontent_makeavailable(glfw)

set(GLAD_LOCATION ${CMAKE_SOURCE_DIR}/thirdparty/glad)

add_executable(modificate_client
    client.c
    window.c
    camera.c
    chunk.c
    atlas.c
    ${GLAD_LOCATION}/src/gl.c
)
target_link_libraries(modificate_client PRIVATE glfw modificate_shared)
target_include_directories(modificate_client SYSTEM PRIVATE ${GLAD_LOCATION}/include)

set_target_properties(modificate_client PROPERTIES
    MACOSX_BUNDLE ON
    MACOSX_FRAMEWORK_IDENTIFIER com.rwilliaise.modificate)
