
#include <script/Vm.h>
#include <iostream>
#include <string>

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
	
	Vm::Vm() {
		lua_State *L = lua_newstate(basicAlloc, this);
		state = std::shared_ptr<void>(L, [](void *p) {
			lua_close((lua_State *) p);
		});

		lua_setwarnf(L, [](void* /* ud */, const char *msg, int /* tocont */) {
			std::cerr << msg << std::endl;
		}, nullptr);
		luaL_openlibs(L);

		// base libs

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
	}

	void Vm::open(std::vector<char> mem, std::string name) {
		open(std::string(mem.data(), mem.size()), name);
	}

	void Vm::open(std::string str, std::string name) {
		lua_State *L = getState(*this);
		luaL_loadstring(L, str.c_str());
		lua_call(L, 0, 1);
	}

} // sh

