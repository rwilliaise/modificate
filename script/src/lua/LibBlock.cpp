
#include "LibBlock.h"

#define toluablock(L) ((LuaBlock *) luaL_checkudata(L, 1, LUA_BLOCK))

namespace sh {

	static int blockToString(lua_State *L) {
		LuaBlock *p = toluablock(L);
		if (p->registered) 
			lua_pushliteral(L, "block (unregistered)");
		else
			lua_pushfstring(L, "block (%s)", p->id.c_str());
		return 1;
	}

	static int blockRegister(lua_State *L) {
		LuaBlock *p = toluablock(L);
		if (p->registered)
			luaL_error(L, "attempt to reregister");
	}

	static LuaBlock *newLuaBlock(lua_State *L) {

	}

	static const luaL_Reg metameth[] = {
		{"__index", NULL},
		{"__tostring", blockToString},
		{NULL, NULL}
	};

	static const luaL_Reg meth[] = {
		{"register", blockRegister},
		{NULL, NULL}
	};

	static void createMeta(lua_State *L) {
		luaL_newmetatable(L, LUA_BLOCK);
		luaL_setfuncs(L, metameth, 0);
		luaL_newlibtable(L, l);
	}


	int openlib_block(lua_State *L) { 
		
		return 1;
	}

} // sh
