
#include "LuaWorld.h"
#include "lua.h"
#include <iostream>

namespace sh {

	static const World *getWorld(lua_State *L) {
		lua_getfield(L, LUA_REGISTRYINDEX, "_WORLD");
#ifndef NDEBUG
		if (!lua_islightuserdata(L, -1)) {
			// if control flow ever gets here: oh no
			std::cerr << "World access - non light userdata. Hopefully not a cosmic ray." << std::endl;
			luaL_error(L, "World access: non light userdata. This may be very bad.");
		}
#endif
		return static_cast<World*>(lua_touserdata(L, -1));
	}

	static int mountWorldLib(lua_State *L) {
		
		return true;
	}

	void openWorldLib(lua_State *L, std::shared_ptr<World> world) {
		// the lifetime of the world should be longer than the vm... hopefully! :)
		lua_pushlightuserdata(L, world.get()); 
		lua_setfield(L, LUA_REGISTRYINDEX, "_WORLD");

		luaL_requiref(L, LIB_WORLDNAME, mountWorldLib, true);
	}
} // sh
