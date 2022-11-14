
#include <script/Vm.h>
#include <iostream>
#include <string>

#include "LibBlock.h"

#include <lua.hpp>

namespace sh {

	class World;

	/** Some filesystem globals are banned and removed from default libs. */
	static const char *bannedGlobals[] = {
		"collectgarbage", // TODO: restricted version
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
		
		luaL_openlibs(L);

		for (auto global : bannedGlobals) {
			lua_pushnil(L);
			lua_setglobal(L, global);
		}
	}

	bool Vm::open(std::vector<char> mem, std::string name) {
		return open(std::string(mem.data(), mem.size()), name);
	}

	bool Vm::open(std::string str, std::string name) {
		lua_State *L = getState(*this);
		return luaL_dostring(L, str.c_str()) == LUA_OK;
	}

} // sh


