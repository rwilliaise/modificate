
#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include <glm/ext/vector_uint3_sized.hpp>

#include "World.h"

constexpr auto CHUNK_SIZE = 16;

namespace sh {

	class Chunk {
	public:
		bool setBlock(glm::u8vec3 pos, std::string identifier);

		inline auto getWorld() { return world; }
		inline auto getBlock(size_t x, size_t y, size_t z) {
			return blocks[x][y][z];
		}

	private:
		friend class World;

		std::shared_ptr<World> world;
		uint16_t blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]; // 8192 bytes

	};

} // sh

