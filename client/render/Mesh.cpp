
#include "Mesh.h"
#include "shared/Chunk.h"

#include <glm/ext/vector_int4.hpp>
#include <pmmintrin.h>
#include <smmintrin.h>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <xmmintrin.h>

namespace r {

	static const glm::ivec4 SIDES[] = {
		glm::ivec4(1, 0, 0, 0), glm::ivec4(0, 1, 0, 0), glm::ivec4(0, 0, 1, 0), // west, up, north
		glm::ivec4(-1, 0, 0, 0), glm::ivec4(0, -1, 0, 0), glm::ivec4(0, 0, -1, 0), // east, down, south 
	};

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

		std::vector<glm::vec3> data;

		try {
			for (size_t x = 0; x < CHUNK_SIZE; x++) {
				for (size_t y = 0; y < CHUNK_SIZE; y++) {
					for (size_t z = 0; z < CHUNK_SIZE; z++) {
						uint16_t pBlock = chunk.getBlock(x, y, z);

						if (pBlock == sh::AIR_BLOCK) {
							continue;
						}

						auto id = palette.at(pBlock);
						auto block = world->registered.at(id);

#ifdef R_SIMD_ENABLED
						glm::ivec4 pos(x, y, z, 0);
#else
						glm::ivec3 pos(x, y, z);
#endif

						for (const auto& side : SIDES) {
#ifdef R_SIMD_ENABLED
							static const __m128 zero = { 0, 0, 0, 0 };
							static const __m128 mChunk = { CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE };

							__m128 add = _mm_hadd_ps(reinterpret_cast<const __m128&>(pos), reinterpret_cast<const __m128&>(side));
							float *vec = reinterpret_cast<float *>(&add);

							__m128 greater = _mm_cmpge_ps(add, mChunk);
							__m128 lesser = _mm_cmplt_ps(add, zero);
							__m128 combine = _mm_or_ps(greater, lesser);
							__m128i iCombine = reinterpret_cast<__m128i>(combine);
							
							if (_mm_testz_si128(iCombine, iCombine)) {
								continue;
							}
							
							auto neighbor = chunk.getBlock(vec[0], vec[1], vec[2]);

#else
							glm::ivec3 vec = pos + side; 

							if (vec.x >= CHUNK_SIZE ||
								vec.y >= CHUNK_SIZE ||
								vec.z >= CHUNK_SIZE) {
								continue;
							}
							if (vec.x < 0 ||
								vec.y < 0 ||
								vec.z < 0) {
								continue;
							}

							auto neighbor = chunk.getBlock(vec.x, vec.y, vec.z);
#endif
							
							if (neighbor == sh::AIR_BLOCK) { 
								// TODO: other non-solid blocks?
								data.reserve(data.size() + 8); // 4 verts, 4 texture coords
							}
						}
					}
				}
			}
		} catch (std::out_of_range& e) {
			std::cerr << e.what() << std::endl;
		}


		return true;
	}
} // r
