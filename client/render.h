
#ifndef RENDER_H_
#define RENDER_H_

typedef struct render_ctx render_ctx_t;

render_ctx_t *render_open(int width, int height);
int render_loop(render_ctx_t *ctx);
int render_close(render_ctx_t *ctx);

#endif // RENDER_H_
