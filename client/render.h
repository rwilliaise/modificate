
#ifndef RENDER_H_
#define RENDER_H_

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <shared/world.h>

/* Mesh representing one chunk. */
typedef struct {
    world_chunk_t *chunk; // the current chunk this mesh represents
    GLuint vao;
    GLuint vbos[2];
} r_chunk_t;

extern GLFWwindow *loaded_window;
extern r_chunk_t *unloaded[4]; // used to hold unused meshes for new chunks

int r_open(int width, int height);
int r_loop();
int r_close();

r_chunk_t *r_chunk_load(world_chunk_t *world_chunk);
/** rebuilds chunk mesh */
int r_chunk_rebuild(r_chunk_t *chunk);
/** changes the chunk associated with this mesh */
int r_chunk_reassociate(r_chunk_t *chunk, world_chunk_t *world_chunk);

#endif // RENDER_H_
