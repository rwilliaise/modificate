
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include <shared/log.h>

#include "render.h"

struct render_ctx {
    GLFWwindow *win;
};

static void render_resize_callback(GLFWwindow *win, int width, int height) {
    glViewport(0, 0, width, height);
}

static void render_error_callback(int error, const char *desc) {
    log_log(LOG_ERROR, "GLFW ERROR: %d: %s", error, desc);   
}

render_ctx_t *render_open(int width, int height) {
    glfwSetErrorCallback(render_error_callback);

    if (glfwInit() != GLFW_TRUE) {
        return NULL;
    }

    // always latest
    // TODO: check if this works cross-platform
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    GLFWwindow *win = glfwCreateWindow(width, height, "modificate " MODIFICATE_VERSION, NULL, NULL);


    render_ctx_t *ctx = malloc(sizeof(render_ctx_t));
    if (!ctx) {
        log_log(LOG_ERROR, "out of memory!");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(win);
    gladLoadGL(glfwGetProcAddress);

    glfwSetWindowUserPointer(win, ctx);
    glfwSetWindowSizeCallback(win, render_resize_callback);

    glViewport(0, 0, width, height);
    
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

