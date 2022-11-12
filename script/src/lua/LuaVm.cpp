
#include <script/Vm.h>
#include <iostream>
#include <string>

#include "LibBlock.h"

extern "C" {

#ifndef NDEBUG
#define LUA_USE_APICHECK
#endif

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdlib.h>

}

namespace sh {

	class World;

	/** Some filesystem globals are banned and removed from default libs. */
	static const char *bannedGlobals[] = {
		"dofile",
		"loadfile",
		"collectgarbage", // TODO: restricted version
		"require", // TODO: restricted version
	};

	static const char *bannedIoGlobals[] = {
		"open",
		"popen",
		"input",
		"output",
		"lines"
	};

	static const luaL_Reg defaultLibs[] = {
		{LUA_GNAME, luaopen_base},
		// {LUA_LOADLIBNAME, luaopen_package}, TODO
		{LUA_COLIBNAME, luaopen_coroutine},
		{LUA_TABLIBNAME, luaopen_table},
		{LUA_IOLIBNAME, luaopen_io},
		{LUA_OSLIBNAME, luaopen_os},
		{LUA_STRLIBNAME, luaopen_string},
		{LUA_MATHLIBNAME, luaopen_math},
		{LUA_UTF8LIBNAME, luaopen_utf8},
		// {LUA_DBLIBNAME, luaopen_debug}, TODO
		{"Block", openlib_block},
	};

	static void *basicAlloc(void * /* ud */, 
							void *ptr,
							size_t /* osize */,
							size_t nsize) {
		if (nsize == 0) { // free
			free(ptr);
			return nullptr;
		} else { // realloc(std::nullptr_t, size_t) is analogous to malloc
			return realloc(ptr, nsize);
		}
	}

	static inline lua_State *getState(Vm& vm) {
		return (lua_State *) vm.get();
	}
	
	Vm::Vm(std::shared_ptr<World> world): world(world) {
		lua_State *L = lua_newstate(basicAlloc, nullptr);
		state = std::shared_ptr<void>(L, [](void *p) {
			lua_close((lua_State *) p);
		});

		lua_setwarnf(L, [](void* /* ud */, const char *msg, int /* tocont */) {
			std::cerr << msg << std::endl;
		}, nullptr);

		// base libs
		
		for (auto reg : defaultLibs) {
			luaL_requiref(L, reg.name, reg.func, 1);
			lua_pop(L, 1);
		}

		for (auto global : bannedGlobals) {
			lua_pushnil(L);
			lua_setglobal(L, global);
		}

		lua_getglobal(L, "io");
		for (auto ioGlobal : bannedIoGlobals) {
			lua_pushstring(L, ioGlobal);
			lua_pushnil(L);
			lua_settable(L, 1);
		}
		lua_pop(L, 1);
	}

	bool Vm::open(std::vector<char> mem, std::string name) {
		return open(std::string(mem.data(), mem.size()), name);
	}

	bool Vm::open(std::string str, std::string name) {
		lua_State *L = getState(*this);
		return luaL_dostring(L, str.c_str()) == LUA_OK;
	}

} // sh


