
#include <shared/filesystem.h>

#include <pthread.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "render.h"

char *fs_running_directory;

struct start_ctx { // derived from program arguments
    int width, height;
    char *running_directory;
};

static int start(struct start_ctx *ctx) {
    char path[PATH_MAX];
    realpath(ctx->running_directory, path);
    fs_running_directory = path;

    if (r_open(ctx->width, ctx->height)) { return 1; }
    return r_loop();
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
            else if (strcmp(arg, "-r") == 0 || strcmp(arg, "--run") == 0)
                mode = 3;
            else if (strcmp(arg, "--help") == 0) {
                printf( "Usage: modificate_client [OPTIONS]\n\n"
                        "Available options:\n"
                        "--help\t\tprints this dialog.\n"
                        "-w\t\tsets the width of the client window.\n"
                        "-h\t\tsets the height of the client window.\n");
                return 0;
            } else
                mode = 4;
            break;
        case 1: // -w
            ctx.width = atoi(arg);
            mode = 0;
            break;
        case 2: // -h
            ctx.height = atoi(arg);
            mode = 0;
            break;
        case 3: // -r and --run

        default:
            break;
        }
    }

    return start(&ctx);
}

