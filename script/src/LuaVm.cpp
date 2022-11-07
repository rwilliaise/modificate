
#include <script/Vm.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdlib.h>

namespace scr {

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
	}

} // scr

