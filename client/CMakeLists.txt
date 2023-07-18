
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)

fetchcontent_declare(glfw
    GIT_REPOSITORY  https://github.com/glfw/glfw.git
    GIT_TAG         3.3.8
)
fetchcontent_makeavailable(glfw)

add_executable(modificate_client
    client.c
)
target_link_libraries(modificate_client PRIVATE glfw)
