
#include "Mesh.h"

#include <iostream>
#include <stdexcept>

namespace r {

	Mesh::Mesh() {
		glGenVertexArrays(1, &vao);
		glGenBuffers(3, buffers);
	}

	Mesh::~Mesh() {
		glDeleteBuffers(3, buffers);
		glDeleteVertexArrays(1, &vao);
	}

	bool Mesh::update(sh::Chunk &chunk) {
		auto world = chunk.getWorld();
		const auto &palette = world->getPalette();

		try {
			for (size_t x = 0; x < CHUNK_SIZE; x++) {
				for (size_t y = 0; y < CHUNK_SIZE; y++) {
					for (size_t z = 0; z < CHUNK_SIZE; z++) {
						uint16_t pBlock = chunk.getBlock(x, y, z);
						auto id = palette.at(pBlock);
						auto block = world->registered.at(id);
						
					}
				}
			}
		} catch (std::out_of_range& e) {
			std::cerr << e.what() << std::endl;
		}


		return true;
	}
} // r
