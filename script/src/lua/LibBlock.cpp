
#include "LibBlock.h"
#include <cstring>

#define toluablock(L) ((LuaBlock *) luaL_checkudata(L, 1, LUA_BLOCK))

namespace sh {
	struct LuaBlock {
		char *id;
		Block *block;
		int registered;
	};

	static int blockToString(lua_State *L) {
		LuaBlock *p = toluablock(L);
		if (p->registered) 
			lua_pushliteral(L, "block (unregistered)");
		else
			lua_pushfstring(L, "block (%s)", p->id ? p->id : "null");
		return 1;
	}

	static int blockRegister(lua_State *L) {
		LuaBlock *p = toluablock(L);
		if (p->registered)
			luaL_error(L, "attempt to reregister");
		size_t size;
		const char *id = lua_tolstring(L, -2, &size);
		std::memcpy(&p->id, id, size);
		return 1;
	}

	static int newLuaBlock(lua_State *L) {
		LuaBlock *p = static_cast<LuaBlock*>(lua_newuserdatauv(L, sizeof(LuaBlock), 0));
		p->block = nullptr;
		p->id = nullptr;
		p->registered = false;

		luaL_setmetatable(L, LUA_BLOCK);
		return 1;
	}

	static const luaL_Reg blockLib[] = {
		{"new", newLuaBlock},
		{nullptr, nullptr}
	};

	static const luaL_Reg metameth[] = {
		{"__index", nullptr},
		{"__tostring", blockToString},
		{nullptr, nullptr}
	};

	static const luaL_Reg meth[] = {
		{"register", blockRegister},
		{nullptr, nullptr}
	};

	static void createMeta(lua_State *L) {
		luaL_newmetatable(L, LUA_BLOCK);
		luaL_setfuncs(L, metameth, 0);
		luaL_newlibtable(L, meth);
		luaL_setfuncs(L, meth, 0);
		lua_setfield(L, -2, "__index");
		lua_pop(L, 1);
	}

	int openlib_block(lua_State *L) { 
		luaL_newlib(L, blockLib);
		createMeta(L);
		return 1;
	}

} // sh
