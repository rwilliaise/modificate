
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

add_executable(modificate_client
    client.c
    render.c
)
target_link_libraries(modificate_client PRIVATE glfw cglm)
