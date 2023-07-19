
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "render.h"

struct render_ctx {
    GLFWwindow *win;
};

static void render_error_callback(int error, const char *desc) {
    
}

render_ctx_t *render_open(int width, int height) {
    glfwSetErrorCallback(render_error_callback);

    if (glfwInit() != GLFW_TRUE) {
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    GLFWwindow *win = glfwCreateWindow(width, height, "modificate " MODIFICATE_VERSION, NULL, NULL);

    render_ctx_t *ctx = malloc(sizeof(render_ctx_t));
    if (!ctx) {
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(win);
    gladLoadGL(glfwGetProcAddress);
    
    ctx->win = win;
    return ctx;
}

int render_loop(render_ctx_t *ctx) {
    while (!glfwWindowShouldClose(ctx->win)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(ctx->win);
        glfwPollEvents();
    }
    return 0;
}

