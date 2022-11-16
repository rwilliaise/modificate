
#include "LibBlock.h"

#include <script/Vm.h>
#include <iostream>
#include <string>

namespace sh {

	class World;

	const static luaL_Reg mod_libs[] = {
		{"block", openlib_block},
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
		global = std::shared_ptr<void>(L, [](void *p) {
			lua_close((lua_State *) p);
		});

		lua_setwarnf(L, [](void* /* ud */, const char *msg, int /* tocont */) {
			std::cerr << msg << std::endl;
		}, nullptr);

		luaL_openlibs(L);

		for (auto reg : mod_libs) {
			luaL_requiref(L, reg.name, reg.func, 1);
			lua_pop(L, -1);
		}
	}

	void Vm::split(Mod &mod) {
		if (mod.context != nullptr)
			std::cout << "WARNING: Mod VM already split - this may be very bad" << std::endl;
		std::cout << "Split mod state" << std::endl;
		mod.context = std::shared_ptr<void>(lua_newthread(getState(*this)), [](void *) {});
	}
} // sh


