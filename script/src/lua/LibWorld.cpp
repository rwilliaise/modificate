
#include "LibWorld.h"
#include <world/World.h>

namespace sh {

	static World *getWorld(lua_State *L) {
		lua_getfield(L, LUA_REGISTRYINDEX, LUA_WORLD);
		return (World *) luaL_checkudata(L, -1, LUA_WORLD);
	}

	static int setBlock(lua_State *L) {
		
	}

	const static luaL_Reg worldlib[] = {
		{"setBlock", setBlock},
	};

	int openlib_world(lua_State *L) {
		luaL_newlib(L, worldlib);
		return 1;
	}

} // sh
