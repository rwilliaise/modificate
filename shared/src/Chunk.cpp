
#include <shared/Chunk.h>

namespace sh {

	bool Chunk::setBlock(glm::u8vec3 pos, std::string identifier) {
		if (pos.x > CHUNK_SIZE - 1 || 
			pos.y > CHUNK_SIZE - 1 ||
			pos.z > CHUNK_SIZE - 1) {
			return false;
		}

		uint16_t palette = UINT16_MAX;
		for (auto pair : world->palette) {
			if (pair.second == identifier) {
				palette = pair.first;
				break;
			}
		}

		if (palette == UINT16_MAX) {
			palette = world->next;
			world->palette.insert({ world->next++, identifier });
		}

		blocks[pos.x][pos.y][pos.z] = palette;
		return true;
	}

} // sh 

