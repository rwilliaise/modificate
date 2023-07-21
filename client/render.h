
#ifndef RENDER_H_
#define RENDER_H_

#include <glad/gl.h>
#include <shared/world.h>

/* Mesh representing one chunk. */
typedef struct {
    world_chunk_t *chunk; // the current chunk this mesh represents
    GLuint built_verts;
    GLuint vao;
    GLuint vbos[3]; // 0 -> pos, 1 -> normal, 2 -> uv
} r_chunk_t;

int r_open(int width, int height);
int r_loop();
int r_close();

r_chunk_t *r_chunk_load(world_chunk_t *world_chunk);
void r_chunk_unload(r_chunk_t *chunk);
/** rebuilds chunk mesh */
int r_chunk_rebuild(r_chunk_t *chunk);
int r_chunk_render(r_chunk_t *chunk);

#endif // RENDER_H_
