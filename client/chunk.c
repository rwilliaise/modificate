#include <shared/world.h>
#include <shared/log.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "render.h"

#define R_UNLOADED_MAX 4

int unloaded_amount = 0;
r_chunk_t *unloaded[R_UNLOADED_MAX]; // holds unused meshes for later use

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
    chunk->layer_count = 0;
    chunk->layers = NULL;

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

int r_chunk_unload(r_chunk_t *chunk) {
    if (chunk == NULL) { return 1; }

    if (unloaded_amount < R_UNLOADED_MAX) {
        chunk->chunk = NULL;
        unloaded[unloaded_amount++] = chunk;
        return 0;
    }

    glDeleteBuffers(3, chunk->vbos);
    glDeleteVertexArrays(1, &chunk->vao);

    free(chunk);
    return 0;
}

int r_chunk_rebuild(r_chunk_t *chunk) {
    if (chunk == NULL || chunk->chunk == NULL) { return 1; }
    world_chunk_t *world_chunk = chunk->chunk;

    log_debug("TODO: chunk building");

    return 0;
}

int r_chunk_render(r_chunk_t *chunk) {
    if (chunk == NULL || chunk->layer_count == 0) { return 1; }

    glBindVertexArray(chunk->vao);

    for (int i = 0; i < chunk->layer_count; i++) { 
        struct r_chunk_layer *layer = &chunk->layers[i];
        glDrawArrays(GL_TRIANGLES, layer->start, layer->verts);
    }

    return 0;
}

