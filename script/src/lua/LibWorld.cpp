
#include "LibWorld.h"

namespace sh {

	static int setBlock(lua_State *L) {
		lua_getfield(L, LUA_REGISTRYINDEX, LUA_WORLD);
		luaL_checkudata(L, -1, LUA_WORLD);
	}

	const static luaL_Reg worldlib[] = {
		{"setBlock", 
	};

	int openlib_world(lua_State *L) {
		luaL_newlib(L, l);
		return 1;
	}

} // sh
