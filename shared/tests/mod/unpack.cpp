/**
 * Loads mod.tar and makes sure that mod.json is found
 */

#include <exception>
#include <iterator>
#include <fstream>
#include <iostream>

#include <shared/Mod.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: unpack [FILE]" << std::endl;
		return 1;
	}
	try {
		std::ifstream stream(argv[1], std::ios::binary | std::ios::ate);
		std::streampos size = stream.tellg();
		stream.seekg(0, std::ios::beg);

		std::vector<char> mem(size);
		stream.read(mem.data(), mem.size());

		stream.close();

		sh::Mod mod;
		mod.tar_loadFromMemory(mem);

		std::cout << "count: " << mod.vfs.size() << std::endl;
		for (auto pair : mod.vfs) {
			std::cout << pair.first << ":\t\t\"" << std::string(pair.second.data(), pair.second.size()).c_str() << "\"" << std::endl;
		}
		
		auto modJson = mod.vfs.find("mod.json");
		if (modJson == mod.vfs.end()) {
			return 1;
		}

		return 0;
	} catch (std::exception& e) {
		std::cerr << argv[1] << ": " << e.what() << std::endl;
	}
	return 1;
}
