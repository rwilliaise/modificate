
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)

fetchcontent_declare(glfw
    GIT_REPOSITORY  https://github.com/glfw/glfw.git
    GIT_TAG         3.3.8
)
fetchcontent_declare(cglm
    GIT_REPOSITORY  https://github.com/recp/cglm
    GIT_TAG         v0.9.0
)
fetchcontent_makeavailable(glfw cglm)

set(GLAD_LOCATION ${CMAKE_SOURCE_DIR}/thirdparty/glad)

add_executable(modificate_client
    client.c
    render.c
    ${GLAD_LOCATION}/src/gl.c
)
target_link_libraries(modificate_client PRIVATE glfw cglm)
target_include_directories(modificate_client PRIVATE ${GLAD_LOCATION}/include)
