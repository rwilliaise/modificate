
#ifndef R_ATLAS_H_
#define R_ATLAS_H_

#include <cglm/vec2.h>
#include <glad/gl.h>

#include <stdint.h>

typedef struct {
    GLuint texture_id;
    uint32_t object_count;
    struct r_atlas_text_object {
        char character;
        vec2 start, end;
    } objects[0];
} r_atlas_text_t;

typedef struct {
    GLuint texture_id;
    uint32_t object_count;
    struct r_atlas_generic_object {
        char *id;
        vec2 start, end;
    } objects[0];
} r_atlas_generic_t;

r_atlas_text_t *r_atlas_text_generate_bitmap();

r_atlas_generic_t *r_atlas_generic_generate();

#endif // ATLAS_H_
