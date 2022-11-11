
#include "script/Mod.h"
#include <exception>
#include <iterator>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: unpack [FILE]" << std::endl;
		return 1;
	}
	try {
		std::ifstream stream(argv[1], std::ios::binary);
		
		stream.unsetf(std::ios::skipws);

		stream.seekg(0, std::ios::end);
		std::streampos size = stream.tellg();
		stream.seekg(0, std::ios::beg);

		std::vector<char> mem;
		mem.reserve(size);

		mem.insert(mem.begin(),
				   std::istream_iterator<char>(stream),
				   std::istream_iterator<char>());

		stream.close();

		sh::Mod mod;
		mod.tar_loadFromMemory(mem);
		
		auto testLua = mod.vfs.find("script/tests/mod/test.lua");
		if (testLua == mod.vfs.end()) {
			return 1;
		}

		return 0;
	} catch (std::exception& e) {
		std::cerr << argv[1] << ": " << e.what() << std::endl;
	}
}
