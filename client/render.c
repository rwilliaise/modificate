
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "render.h"

struct render_ctx {
    GLFWwindow *win;
};

static void render_error_callback(int error, const char *desc) {
    
}

render_ctx_t *render_open() {
    glfwSetErrorCallback(render_error_callback);

    if (glfwInit() != GLFW_TRUE) {
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    GLFWwindow *win = glfwCreateWindow(640, 480, "modificate " MODIFICATE_VERSION, NULL, NULL);

    render_ctx_t *ctx = malloc(sizeof(render_ctx_t));
    if (!ctx) {
        glfwTerminate();
        return NULL;
    }
    
    return ctx;
}

