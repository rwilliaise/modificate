/**
 * Nano-implementation of tar unarchive.
 * Very insecure
 */

#include <script/Mod.h>
#include <iostream>
#include <cstring>
#include <string>
#include <utility>

namespace sh {
	
	static uint64_t parseOctalString(char *curr, uint32_t size) {
		uint64_t out = 0;
		while (size > 0) {
			out =  out * 8 + *(curr++) - '0';
			size--;
		}
		return out;
	}

	void Mod::tar_loadFromMemory(std::vector<char> mem) {
		for (size_t i = 0; i < mem.size();) {
			if (std::string(&mem[i + 257], 5) != "ustar") {
				return;
			}
			std::string filename(&mem[i]);
			uint64_t size = parseOctalString(&mem[i + 124], 12);
			uint8_t type = mem[i + 156];

			i += 512;

			switch (type) {
			case 0:
			case '0':
				std::vector<char> file(size);
				std::memcpy(file.data(), &mem[i], size);
				vfs[filename] = file;
				i += size;
				break;
			}

		}
	}
}
