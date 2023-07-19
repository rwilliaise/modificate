
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#include "def.h"
#include "render.h"

struct start_ctx { // derived from program arguments
    int width, height;
};

static int start(struct start_ctx *ctx) {
    render_ctx_t *R = render_open(ctx->width, ctx->height);
    return render_loop(R);
}

// TODO: WinMain, macOS main, others
int main(int argc, char *argv[]) {
    struct start_ctx ctx = { 640, 480 };

    int mode = 0;
    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];
        switch (mode) {
        case 0:
            if (strcmp(arg, "-w") == 0)
                mode = 1;
            else if (strcmp(arg, "-h") == 0)
                mode = 2;
            else if (strcmp(arg, "--help") == 0)
                mode = -1;
            else
                mode = 3;
            break;
        case 1: // -w
            ctx.width = atoi(arg);
            mode = 0;
            break;
        case 2: // -h
            ctx.height = atoi(arg);
            mode = 0;
            break;
        default:
            printf( "Usage: modificate_client [OPTIONS]\n\n"
                    "Available options:\n"
                    "--help\t\tprints this dialog.\n"
                    "-w\t\t\tsets the width of the client window.\n"
                    "-h\t\t\tsets the height of the client window.\n");
        case 3:
            break;
        }
    }

    return start(&ctx);
}

