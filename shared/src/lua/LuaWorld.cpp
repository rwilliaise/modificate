
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
	static const char *BLOCK_GLOBALTABLE = "_BLOCKS";

	static World *getWorld(lua_State *L) {
		lua_getfield(L, LUA_REGISTRYINDEX, "_WORLD");
#ifndef NDEBUG
		if (!lua_islightuserdata(L, -1)) {
			// if control flow ever gets here: oh no
			std::cerr << "World access - non light userdata. Hopefully not a cosmic ray." << std::endl;
			luaL_error(L, "World access: non light userdata. This may be very bad.");
		}
#endif
		return static_cast<World *>(lua_touserdata(L, -1));
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

	static int blockNewIndex(lua_State *L) {
		LuaBlock *block = getBlock(L);
		const char *key = luaL_checkstring(L, 2);

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
	

		return true;
	}

	static int mountWorldLib(lua_State *L) {
		luaL_newlib(L, worldMethods);

		lua_newtable(L); // storage table for block userdatas
		lua_setfield(L, -1, BLOCK_GLOBALTABLE);

		return true;
	}

	void openWorldLib(lua_State *L, std::shared_ptr<World> world) {
		// the lifetime of the world should be longer than the vm... hopefully! :)
		lua_pushlightuserdata(L, world.get()); 
		lua_setfield(L, LUA_REGISTRYINDEX, "_WORLD");
		luaL_requiref(L, LIB_WORLDNAME, mountWorldLib, true);
	}
} // sh
