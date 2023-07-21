
#include <shared/world.h>
#include <stdlib.h>

#include <shared/log.h>

#include <glad/gl.h>
#include "GLFW/glfw3.h"
#include "render.h"

GLFWwindow *loaded_window = NULL;
r_chunk_t *unloaded[4] = { 0, 0, 0, 0 };

static void r_resize_callback(GLFWwindow *win, int width, int height) {
    glViewport(0, 0, width, height);
}

static void r_gl_error_callback(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar *message,
        const void *ud
) {
    enum log_severity logging_severity;
    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        logging_severity = LOG_ERROR;
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
    case GL_DEBUG_SEVERITY_LOW:
        logging_severity = LOG_WARN;
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        logging_severity = LOG_DEBUG;
        break;
    }


    log_log(logging_severity, "GL: %s", message);
}

static void r_glfw_error_callback(int error, const char *desc) {
    log_log(LOG_ERROR, "GLFW ERROR: %d: %s", error, desc);   
}

int r_open(int width, int height) {
    glfwSetErrorCallback(r_glfw_error_callback);

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

    if (loaded_gl_version == 0) {
        log_log(LOG_ERROR, "Failed to load GL!");
        glfwTerminate();
        return 1;
    }

    log_log(LOG_INFO, "Loaded GL version: %d.%d", GLAD_VERSION_MAJOR(loaded_gl_version), GLAD_VERSION_MINOR(loaded_gl_version));

    if (GLAD_VERSION_MAJOR(loaded_gl_version) != 4 ||
        GLAD_VERSION_MINOR(loaded_gl_version) != 6) {
        log_log(LOG_WARN, "GL version is out of date!");
    }

    glfwSetWindowSizeCallback(win, r_resize_callback);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(r_gl_error_callback, NULL);
    glViewport(0, 0, width, height);
    
    loaded_window = win;
    return 0;
}

int r_loop() {
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

r_chunk_t *r_chunk_create(world_chunk_t *world_chunk) {
    if (world_chunk == NULL) {
        return NULL;
    }

    r_chunk_t *chunk = malloc(sizeof(r_chunk_t));
    if (chunk == NULL) {
        return NULL;
    }
}
