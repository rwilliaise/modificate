/**
 * Nano-implementation of tar unarchive
 */

#include <script/Mod.h>
#include <string>

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
		for (int i = 0; i < mem.size(); i++) {
			std::string filename(mem[i], 100);
			uint64_t size = parseOctalString(&mem[124], 12);
			uint8_t type = mem[156];

			i += 512;
		}
	}
}
