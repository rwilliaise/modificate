
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include <shared/log.h>

#include "render.h"

GLFWwindow *loaded_window = NULL;

struct render_ctx {
    GLFWwindow *win;
};

struct render_vao {
    GLint vao;
};

static void render_resize_callback(GLFWwindow *win, int width, int height) {
    glViewport(0, 0, width, height);
}

static void render_error_callback(int error, const char *desc) {
    log_log(LOG_ERROR, "GLFW ERROR: %d: %s", error, desc);   
}

int render_open(int width, int height) {
    glfwSetErrorCallback(render_error_callback);

    if (glfwInit() != GLFW_TRUE) {
        return 1;
    }

    // always latest
    // TODO: check if this works cross-platform
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    GLFWwindow *win = glfwCreateWindow(width, height, "modificate " MODIFICATE_VERSION, NULL, NULL);

    glfwMakeContextCurrent(win);
    int loaded_gl_version = gladLoadGL(glfwGetProcAddress);
    log_log(LOG_INFO, "GL version: %d.%d", GLAD_VERSION_MAJOR(loaded_gl_version), GLAD_VERSION_MINOR(loaded_gl_version));

    if (loaded_gl_version != GLAD_GL_VERSION_4_6) {
        log_log(LOG_WARN, "GL version is out of date!");
    }

    glfwSetWindowSizeCallback(win, render_resize_callback);

    glViewport(0, 0, width, height);
    
    loaded_window = win;
    return 0;
}

int render_loop() {
    if (!loaded_window) {
        log_log(LOG_ERROR, "Rendering cannot begin before the window is open.");
        return 1;
    }
    while (!glfwWindowShouldClose(loaded_window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(loaded_window);
        glfwPollEvents();
    }
    return 0;
}

