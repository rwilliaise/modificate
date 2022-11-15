
#include "LibBlock.h"

#include <script/Vm.h>
#include <iostream>
#include <string>
#include <lua.hpp>

namespace sh {

	class World;

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
		global = std::shared_ptr<void>(L, [](void *p) {
			lua_close((lua_State *) p);
		});

		lua_setwarnf(L, [](void* /* ud */, const char *msg, int /* tocont */) {
			std::cerr << msg << std::endl;
		}, nullptr);

		luaL_openlibs(L);
	}

	void Vm::split(Mod &mod) {

	}
} // sh


