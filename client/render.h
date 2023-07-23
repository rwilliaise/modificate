
#ifndef RENDER_H_
#define RENDER_H_

#include <glad/gl.h>
#include <shared/world.h>
#include <cglm/vec3.h>
#include <cglm/mat4.h>
#include <cglm/quat.h>

#include <stdint.h>

#define R_LAYER_GENERIC_PRIORITY 0
#define R_LAYER_CUTOUT_PRIORITY 100
#define R_LAYER_TRANSLUCENT_PRIORITY 200

/* Mesh representing one chunk. */
typedef struct {
    world_chunk_t *chunk; // the current chunk this mesh represents
    /** portions of the chunk rendered in a specific order */
    struct r_chunk_layer {
        uint32_t start; // starting vertex
        uint32_t verts; // vertex count of layer
        GLuint program; // shader program id
    } *layers;
    uint8_t layer_count;
    GLuint vao;
    GLuint vbos[3]; // 0 -> pos, 1 -> normal, 2 -> uv
} r_chunk_t;

typedef struct {
    vec3 pos;
    float fov;
    versor rot;
    mat4 view;
} r_camera_t;

extern r_camera_t *r_camera;

int r_open(int width, int height);
int r_loop();
int r_close();

r_chunk_t *r_chunk_load(world_chunk_t *world_chunk);
void r_chunk_unload(r_chunk_t *chunk);
/** rebuilds chunk mesh */
int r_chunk_rebuild(r_chunk_t *chunk);
int r_chunk_render(r_chunk_t *chunk);

#endif // RENDER_H_
