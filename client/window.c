
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <shared/log.h>

#include "stb_image.h"
#include "render.h"

GLFWwindow *r_win = NULL;
int r_win_width = 0, r_win_height = 0;

static void r_resize_callback(GLFWwindow *win, int width, int height) {
    log_debug("window resized, width = %d, height = %d", width, height);
    glViewport(0, 0, width, height);

    r_win_width = width;
    r_win_height = height;
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
#ifndef NDEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    GLFWwindow *win = glfwCreateWindow(width, height, "� modificate " MODIFICATE_VERSION, NULL, NULL);

    glfwMakeContextCurrent(win);
    int loaded_gl_version = gladLoadGL(glfwGetProcAddress);

    if (loaded_gl_version == 0) {
        log_log(LOG_ERROR, "Failed to load GL!");
        glfwTerminate();
        return 1;
    }
    
    const char *profile;
    switch(glfwGetWindowAttrib(win, GLFW_OPENGL_PROFILE)) {
    case GLFW_OPENGL_CORE_PROFILE: profile = "core"; break;
    case GLFW_OPENGL_COMPAT_PROFILE: profile = "compat"; break;
    default: profile = "unknown";
    }

    log_log(LOG_INFO, "Loaded GL version: %d.%d (%s)", 
            GLAD_VERSION_MAJOR(loaded_gl_version),
            GLAD_VERSION_MINOR(loaded_gl_version), 
            profile);

    if (GLAD_VERSION_MAJOR(loaded_gl_version) != 4 ||
        GLAD_VERSION_MINOR(loaded_gl_version) != 6) {
        log_log(LOG_WARN, "GL version is out of date!");
    }

#ifndef NDEBUG
    if (glfwExtensionSupported("GL_ARB_debug_output") == GLFW_TRUE) {
        log_debug("GL debug enabled.");
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(r_gl_error_callback, NULL);
    }
#endif

    glfwSetWindowSizeCallback(win, r_resize_callback);
    r_resize_callback(win, width, height);
    
    r_win = win;
    return 0;
}

static void r_frame() { 
    r_camera_update();

    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(r_win);
    glfwPollEvents();
}

int r_loop() {
    if (!r_win) {
        log_log(LOG_ERROR, "Rendering cannot begin before the window is open.");
        return 1;
    }
    while (!glfwWindowShouldClose(r_win)) {
        r_frame();
    }
    return 0;
}

int r_close() {
    if (r_win == NULL) {
        return 1;
    }

    glfwTerminate();
    return 0;
}

