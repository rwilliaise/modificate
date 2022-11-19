
#pragma once 

#include <map>
#include <unordered_map>
#include <cstdint>
#include <string>

#include <glm/ext/vector_int3.hpp>
#include <glm/gtx/hash.hpp>

namespace sh {
	class Block;
	class Chunk;

	class World {
	public:

		bool setBlock(glm::ivec3 pos, std::string id);

		std::map<std::string, Block> registered;
	private:
		friend class Chunk;

		uint16_t next = 0;

		std::unordered_map<uint16_t, std::string> palette;
		std::unordered_map<glm::i16vec3, Chunk> chunks;
	};
}

