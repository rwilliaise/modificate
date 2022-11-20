
#include "shared/Mod.h"

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
		lua_State *L = static_cast<lua_State *>(context.get());
		lua_pushfstring(L, "@%s", name.c_str()); // make stacktraces treat name like a filename
		luaL_loadbuffer(L, str.c_str(), str.length(), lua_tostring(L, -1));
		lua_remove(L, -2);
		int err = lua_pcall(L, 0, LUA_MULTRET, 0);
#ifndef NDEBUG
		if (err != LUA_OK) {
			switch (err) {
			case LUA_ERRRUN:
				std::cerr << "runtime error: ";
				break;
			case LUA_ERRMEM:
				std::cerr << "out of memory: ";
				break;
			}

			const char *msg = lua_tostring(L, -1);
			std::cerr << ((msg == nullptr) ? "(null)" : msg) << std::endl;
			std::cout << std::endl;

			luaL_traceback(L, L, NULL, 0);
			std::cerr << lua_tostring(L, -1) << std::endl;
			std::cerr << std::endl;
		}
#endif
		return err == LUA_OK;
	}
} // sh
