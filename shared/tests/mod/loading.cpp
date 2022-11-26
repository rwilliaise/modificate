/**
 * Load the ./tar directory and load valid mods inside the directory.
 */

#include <iostream>
#include <memory>

#include <shared/World.h>
#include <shared/Mod.h>
#include <shared/Vm.h>

#define expect(expr) if (!(expr)) { std::cerr << "Failed test: (expr) == " << (expr) << std::endl; }

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: loading [DIR]" << std::endl;
		return 1;
	}
	auto world = std::make_shared<sh::World>();
	sh::Vm vm(world);
	sh::loadMods(vm, std::string(argv[1]));

	expect(vm.getMods().size() == 1);
	
	const auto& mod = vm.getMods()[0];
	expect(mod.getId() == "test");

	return 0;
}
