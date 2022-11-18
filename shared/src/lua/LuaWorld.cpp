
#include "LuaWorld.h"
#include "lua.h"

#include <algorithm>
#include <iostream>
#include <cstring>
#include <lua.hpp>

namespace sh {

	struct LuaBlock {
		char id[512];
		Block& block;
	};

	static const char *BLOCK_METATABLE = "block";
	static const char *BLOCK_GLOBALTABLE = "registered";

	static World *getWorld(lua_State *L) {
		int idx = lua_upvalueindex(1);
#ifndef NDEBUG
		if (!lua_islightuserdata(L, idx)) {
			// if control flow ever gets here: oh no
			luaL_error(L, "world access failure");
		}
#endif
		return static_cast<World *>(lua_touserdata(L, idx));
	}

	static LuaBlock *getBlock(lua_State *L) {
		return static_cast<LuaBlock *>(luaL_checkudata(L, 1, BLOCK_METATABLE));
	}

	static int block(lua_State *L) {
		World *world = getWorld(L);
		const char *name = luaL_checkstring(L, 1);

		if (name == NULL) {
			luaL_argerror(L, 1, "expected string");
		}

		lua_getfield(L, LUA_REGISTRYINDEX, BLOCK_GLOBALTABLE);
		int type = lua_getfield(L, -1, name);

		if (type != LUA_TNIL) {
			lua_remove(L, -2); // remove global table

			return true;
		}

		LuaBlock *luaBlock = static_cast<LuaBlock *>(lua_newuserdatauv(L, sizeof(LuaBlock), 1));
		luaL_setmetatable(L, BLOCK_METATABLE);

		lua_newtable(L);
		lua_setiuservalue(L, -2, 0);

		Block block;

		std::memcpy(luaBlock->id, name, std::min(static_cast<size_t>(511), std::strlen(name)));
		luaBlock->block = block;
		luaBlock->id[511] = 0;

		world->registerBlock(std::string(name), std::move(block));

		lua_setfield(L, -2, name);
		
		return true;
	}

	static void dumpstack (lua_State *L) {
		std::cout << "current stack: " << std::endl;
		int top=lua_gettop(L);
		for (int i=1; i <= top; i++) {
			printf("%d\t%s\t", i, luaL_typename(L,i));
			switch (lua_type(L, i)) {
				case LUA_TNUMBER:
					printf("%g\n",lua_tonumber(L,i));
					break;
				case LUA_TSTRING:
					printf("%s\n",lua_tostring(L,i));
					break;
				case LUA_TBOOLEAN:
					printf("%s\n", (lua_toboolean(L, i) ? "true" : "false"));
					break;
				case LUA_TNIL:
					printf("%s\n", "nil");
					break;
				default:
					printf("%p\n",lua_topointer(L,i));
					break;
			}
		}
	}

	static int blockNewIndex(lua_State *L) {
		LuaBlock *block = getBlock(L);
		const char *key = luaL_checkstring(L, 2);
		luaL_argcheck(L, lua_isfunction(L, 3), 3, "expected function");
		lua_getiuservalue(L, 1, 0);

		int pastTop = lua_gettop(L);
		lua_pushvalue(L, 3);
		lua_setfield(L, -2, key);
		lua_remove(L, -1);

		return true;
	}

	const luaL_Reg worldMethods[] = {
		{"block", block},
		{nullptr, nullptr},
	};

	const luaL_Reg blockMetaMethods[] = {
		{"__newindex", blockNewIndex},
		{nullptr, nullptr},
	};

	static int createBlockMeta(lua_State *L) {
		luaL_newmetatable(L, BLOCK_METATABLE);
		luaL_setfuncs(L, blockMetaMethods, 0);
		lua_pop(L, -1);

		return true;
	}

	static int mountWorldLib(lua_State *L) {
		luaL_newlibtable(L, worldMethods);
		lua_getfield(L, LUA_REGISTRYINDEX, "_WORLD");
		luaL_setfuncs(L, worldMethods, 1);

		lua_newtable(L); // storage table for block userdatas
		lua_setfield(L, LUA_REGISTRYINDEX, BLOCK_GLOBALTABLE);
		
		return true;
	}

	void openWorldLib(lua_State *L, std::shared_ptr<World> world) {
		// the lifetime of the world should be longer than the vm... hopefully! :)
		lua_pushlightuserdata(L, world.get()); 
		lua_setfield(L, LUA_REGISTRYINDEX, "_WORLD");

		luaL_requiref(L, LIB_WORLDNAME, mountWorldLib, true);
	}
} // sh
