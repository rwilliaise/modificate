/**
 * Runs a lua module and returns a non-zero error code when the module returns
 * a non-truthy value.
 */

#include <iostream>
#include <fstream>

#include <script/Vm.h>
#include <string>

extern "C" {

#include <lua.h>
#include <lauxlib.h>

}

int main(int argc, char *argv[]) {
	if (argc != 2) { 
		std::cerr << "Usage: expect [test]" << std::endl;
		return 1;
	}

	sh::Vm vm;
	vm.open(std::string(argv[1]), "<virtual>");
	
	lua_State *L = (lua_State *) vm.get();
	return !lua_toboolean(L, 1);
}
