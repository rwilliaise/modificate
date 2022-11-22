
#include <boost/json/parse_options.hpp>
#include <shared/Mod.h>
#include <shared/Vm.h>

#include <boost/json.hpp>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <lua.hpp>
#include <fstream>

namespace sh {

	namespace json = boost::json;

	void loadMods(Vm &vm, std::string folder) {
		std::filesystem::path folderPath(folder);
		for (const auto &child : std::filesystem::directory_iterator(folderPath)) {
			if (child.is_regular_file() && child.path().extension() == ".tar") {
				std::ifstream file(child.path());
				std::stringstream str;
				str << file.rdbuf();
				file.close();

				std::string contents = str.str();

				Mod mod;
				mod.tar_loadFromMemory(std::vector(contents.begin(), contents.end()));

				vm.split(std::move(mod));

				if (!mod.mount(vm.getWorld())) {
					std::cerr << "Failed to load mod (" << child.path().filename() << ")" << std::endl;
				}
			}
		}
	}

	bool Mod::mount(std::shared_ptr<World> world) {
		if (context == nullptr) {
			std::cerr << "Main state not split." << std::endl;
			return false;
		}

		auto modFile = vfs.find("mod.json");

		if (modFile == vfs.end()) {
			std::cerr << "mod.json not found." << std::endl;
			return false;
		}
		

		std::string modJsonString(modFile->second.begin(), modFile->second.end());

		json::parse_options opt;
		opt.allow_comments = true;
		opt.allow_trailing_commas = true;
		json::object *modJson = json::parse(modJsonString, {}, opt).if_object();

		if (modJson == nullptr) { return false; }

		auto obj = *modJson; 
		auto jsonId = obj["id"].if_string();

		if (jsonId == nullptr) { return false; }
		
		id = *jsonId;
		
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
