
#ifndef SHARED_MOD_H_
#define SHARED_MOD_H_

#include <stdint.h>

typedef struct {
    // mod permissions
    uint8_t sys_enabled     : 1; // access to the system (bytecode, ffi, jit, fs)
    uint8_t gui_enabled     : 1; // access to creating gui and hud
    uint8_t input_enabled   : 1; // access to capture all inputs
    uint8_t data_enabled    : 1; // access to saving any amount of data to disk
} mod_t;

void mod_load_();

#endif // SHARED_MOD_H_
