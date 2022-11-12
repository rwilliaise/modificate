
#pragma once 

#include <unordered_map>
#include <cstdint>
#include <string>

#include <glm/ext/vector_int3.hpp>
#include <glm/gtx/hash.hpp>

#include "Block.h"

namespace sh {
	class Chunk;

	class World {
	public:

		bool setBlock(glm::ivec3 pos, std::string id);

		inline void registerBlock(std::string identifier, Block&& block) {
			registered.insert({ identifier, block });
		}

	private:
		friend class Chunk;

		uint16_t next = 0;

		std::unordered_map<uint16_t, std::string> palette;
		std::unordered_map<glm::i16vec3, Chunk> chunks;
		std::unordered_map<std::string, Block> registered;
	};
}

#include "Chunk.h"
