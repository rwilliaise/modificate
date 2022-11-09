
#include <script/Vm.h>
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
		state = std::shared_ptr<void>(lua_newstate(basicAlloc, this), [](void *p) {
			lua_close((lua_State *) p);
		});
		luaL_openlibs(getState(*this));
	}

	void Vm::open(std::vector<char> mem, std::string name) {
		open(std::string(mem.data(), mem.size()), name);
	}

	void Vm::open(std::string str, std::string name) {
		lua_State *L = getState(*this);
		luaL_loadbuffer(L, str.c_str(), str.size(), name.c_str());
		lua_call(L, 0, 0);
	}

} // sh

