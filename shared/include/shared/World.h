
#pragma once 

#include <unordered_map>
#include <cstdint>
#include <string>
#include <memory>
#include <map>

#include <glm/ext/vector_int3.hpp>
#include <glm/gtx/hash.hpp>

namespace sh {
	const auto AIR_BLOCK = 0;

	class Block;
	class Chunk;

	class World : public std::enable_shared_from_this<World> {
	public:
		World() {}

		bool setBlock(glm::ivec3 pos, std::string id);

		inline const auto &getPalette() { return palette; }

		std::map<std::string, Block> registered;
	private:
		friend class Chunk;

		uint16_t next = 1;

		std::unordered_map<uint16_t, std::string> palette;
		std::unordered_map<glm::i16vec3, Chunk> chunks;
	};
}

#include "Block.h"
#include "Chunk.h"
