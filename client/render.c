#include <shared/world.h>
#include <shared/log.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "render.h"

#define R_UNLOADED_MAX 4

GLFWwindow *loaded_window = NULL;

int unloaded_amount = 0;
r_chunk_t *unloaded[R_UNLOADED_MAX]; // holds unused meshes for later use

// window stuff

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
#ifndef NDEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    GLFWwindow *win = glfwCreateWindow(width, height, "modificate " MODIFICATE_VERSION, NULL, NULL);

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
        log_log(LOG_DEBUG, "GL debug enabled.");
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(r_gl_error_callback, NULL);
    }
#endif

    glfwSetWindowSizeCallback(win, r_resize_callback);
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

// chunk stuff

static r_chunk_t *r_chunk_replace(world_chunk_t *world_chunk) { // finds or creates a new chunk
    if (unloaded_amount > 0) {
        int idx = --unloaded_amount;
        r_chunk_t *target = unloaded[idx];
        target->chunk = world_chunk;
        unloaded[idx] = NULL;
        return target;
    }

    r_chunk_t *chunk = malloc(sizeof(r_chunk_t));
    if (chunk == NULL) {
        return NULL;
    }

    chunk->chunk = world_chunk;
    chunk->built_verts = 0;
    glGenVertexArrays(1, &chunk->vao);
    glGenBuffers(3, chunk->vbos);

    glBindVertexArray(chunk->vao);
    glEnableVertexAttribArray(0); // pos
    glEnableVertexAttribArray(1); // normal
    glEnableVertexAttribArray(2); // uv
    
    return chunk;
}

r_chunk_t *r_chunk_load(world_chunk_t *world_chunk) {
    if (world_chunk == NULL) {
        return NULL;
    }

    r_chunk_t *chunk = r_chunk_replace(world_chunk);
    if (!chunk) {
        return NULL;
    }

    if (r_chunk_rebuild(chunk)) {
        log_log(LOG_WARN, "Failed to build chunk (%d, %d, %d)!",
                world_chunk->chunk_position[0],
                world_chunk->chunk_position[1],
                world_chunk->chunk_position[2]);
    }

    return chunk;
}

void r_chunk_unload(r_chunk_t *chunk) {
    if (unloaded_amount < R_UNLOADED_MAX) {
        chunk->chunk = NULL;
        unloaded[unloaded_amount++] = chunk;
        return;
    }

    glDeleteBuffers(3, chunk->vbos);
    glDeleteVertexArrays(1, &chunk->vao);

    free(chunk);
}

int r_chunk_rebuild(r_chunk_t *chunk) {
    if (chunk == NULL || chunk->chunk == NULL) { return 1; }
    world_chunk_t *world_chunk = chunk->chunk;

    return 0;
}

int r_chunk_render(r_chunk_t *chunk) {
    if (chunk == NULL || chunk->built_verts == 0) { return 1; }

    glBindVertexArray(chunk->vao);
    glDrawArrays(GL_TRIANGLES, 0, chunk->built_verts);

    return 0;
}

