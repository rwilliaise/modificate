
#include "script/Mod.h"

#include <boost/json.hpp>
#include <iostream>
#include <lua.hpp>

namespace sh {

	bool Mod::mount(std::shared_ptr<World> world) {
		if (context == nullptr) {
			std::cerr << "Main state not split." << std::endl;
			return false;
		}

		auto mod = vfs["mod.json"];
		
		return true;
	}

	bool Mod::open(std::vector<char> mem, std::string name) {
		return open(std::string(mem.data(), mem.size()), name);
	}

	bool Mod::open(std::string str, std::string name) {
		lua_State *L = static_cast<lua_State*>(context.get());
		return luaL_dostring(L, str.c_str()) == LUA_OK;
	}
} // sh
