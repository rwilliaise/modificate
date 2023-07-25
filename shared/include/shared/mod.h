
#ifndef SHARED_MOD_H_
#define SHARED_MOD_H_

#include <stdint.h>

typedef struct {
    char *id;
    char *root_path;

    // mod permissions
    uint8_t sys_enabled     : 1; // access to the system (bytecode, ffi, jit, fs)
    uint8_t gui_enabled     : 1; // access to creating gui and hud
    uint8_t input_enabled   : 1; // access to capture all inputs
    uint8_t data_enabled    : 1; // access to saving any amount of data to disk
} mod_t;

int mod_queue(char *root_path);
mod_t *mod_load(char *root_path);

#endif // SHARED_MOD_H_
