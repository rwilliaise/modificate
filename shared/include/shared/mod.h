
#ifndef SHARED_MOD_H_
#define SHARED_MOD_H_

#include <luajit-2.1/lua.h>
#include <stdint.h>

typedef struct {
    lua_State *L;
    // mod permissions
    uint8_t sys_enabled     : 1; // access to the system (bytecode, ffi, jit, fs)
    uint8_t gui_enabled     : 1; // access to creating gui and hud
    uint8_t input_enabled   : 1; // access to capture all inputs
    uint8_t data_enabled    : 1; // access to saving any amount of data to disk
} mod_t;



#endif // SHARED_MOD_H_
