
#pragma once

#include <world/Block.h>
#include <string>

extern "C" {

#include <lua.h>
#include <lauxlib.h>

}

#define LUA_BLOCK "Block"


namespace sh {

	struct LuaBlock {
		std::string id;
		Block *block;
		int registered;

	};

	int openlib_block(lua_State *L);
} // sh

