/**
 * Nano-implementation of tar unarchive
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
		std::cout << "file size: " << mem.size() << std::endl;
		for (size_t i = 0; i < mem.size(); i++) {
			std::cout << "file" << std::endl;
			std::cout << &mem[i + 257] << std::endl;
			printf("%d\n", mem[i]);
			fwrite(&mem[i], sizeof(char), 512, stdout);
			printf("\n");
			if (std::strcmp(&mem[i + 257], "ustar") != 1) {
				return;
			}
			std::string filename(&mem[i], 100);
			std::string linked(&mem[i + 157], 100);
			uint64_t size = parseOctalString(&mem[i + 124], 12);
			uint8_t type = mem[i + 156];
			std::cout << filename << ": " << size << std::endl;
			std::cout << "type: " << type << std::endl;

			i += 512;

			switch (type) {
			case 0:
			case '0':
				std::vector<char> file(size);
				std::memcpy(file.data(), &mem[i], size);

				vfs.insert({ std::move(filename), std::move(file) });
				break;
			}

			i += size;
		}
	}
}
