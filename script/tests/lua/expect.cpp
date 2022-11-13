/**
 * Runs a lua module and returns a non-zero error code when the module returns
 * a non-truthy value.
 */

#include <iostream>
#include <fstream>

#include <memory>
#include <script/Vm.h>
#include <sstream>
#include <string>
#include <world/World.h>

extern "C" {

#include <lua.h>
#include <lauxlib.h>

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
	vm.open(str.str(), "<virtual>");
	
	lua_State *L = (lua_State *) vm.get();
	return !lua_toboolean(L, 1);
}
