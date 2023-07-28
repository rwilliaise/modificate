
#include <modificate/interface.h>

#include <luajit-2.1/luajit.h>
#include <luajit-2.1/lauxlib.h>
#include <luajit-2.1/lualib.h>

static mod_t *luajit_mod;

MODEXPORT void mod_initialize(mod_t *mod) {
    luajit_mod = mod;
}

MODEXPORT bool mod_loader_should_load(mod_t *mod) {
    if (mod_path_exists(mod, "lua")) {
        return true;
    }
    return false;
}

MODEXPORT int mod_loader_load(mod_t *mod) {
    if (mod == NULL) { return 1; }

    lua_State *L = luaL_newstate();
    if (L == NULL) { return 1; }
    
    luaL_openlibs(L);
    mod_loader_attach(mod, luajit_mod, L);

    return 0;
}

