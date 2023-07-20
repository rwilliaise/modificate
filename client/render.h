
#ifndef RENDER_H_
#define RENDER_H_

typedef struct render_vao render_vao_t;
typedef struct render_vbo render_vbo_t;

/**
 * Initializes the rendering environment.
 */
int render_open(int width, int height);
int render_loop();
int render_close();

render_vao_t *render_vao_create(int vbos);
void render_vao_attach(render_vbo_t *vbo);

#endif // RENDER_H_
