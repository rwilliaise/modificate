/**
 * Runs a lua module and returns a non-zero error code when the module returns
 * a non-truthy value.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>

#include <script/Vm.h>
#include <world/World.h>
#include <lua.hpp>

static void dumpstack (lua_State *L) {
	std::cout << "current stack: " << std::endl;
	int top=lua_gettop(L);
	for (int i=1; i <= top; i++) {
		printf("%d\t%s\t", i, luaL_typename(L,i));
		switch (lua_type(L, i)) {
			case LUA_TNUMBER:
				printf("%g\n",lua_tonumber(L,i));
				break;
			case LUA_TSTRING:
				printf("%s\n",lua_tostring(L,i));
				break;
			case LUA_TBOOLEAN:
				printf("%s\n", (lua_toboolean(L, i) ? "true" : "false"));
				break;
			case LUA_TNIL:
				printf("%s\n", "nil");
				break;
			default:
				printf("%p\n",lua_topointer(L,i));
				break;
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: expect [FILE]" << std::endl;
		return 1;
	}
	std::stringstream str;
	std::ifstream file(argv[1]);
	str << file.rdbuf();
	file.close();

	std::shared_ptr<sh::World> world;
	sh::Vm vm(world);
	sh::Mod test;
	vm.split(test);

	std::string out = str.str();
	std::cout << "File size: " << out.size() << std::endl;
	std::cout << std::endl;
	std::cout << "File: \"\"\"" << std::endl;
	std::cout << out << std::endl;
	std::cout << "\"\"\"" << std::endl;
	std::cout << std::endl;

	std::string srcFile = std::string(argv[1]);
	std::string filename = srcFile.substr(srcFile.find_last_of("/\\") + 1);
	bool result = test.open(out, filename);
	
	lua_State *L = (lua_State *) vm.get();
	dumpstack(L);
	return (result && lua_toboolean(L, 1)) ? 0 : 1;
}
