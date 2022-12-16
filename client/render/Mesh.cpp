
#include "Mesh.h"
#include "shared/Chunk.h"

#include <glad/gl.h>
#include <glm/ext/vector_int4.hpp>
#include <glm/geometric.hpp>

#include <stdexcept>
#include <iostream>
#include <vector>
#include <xmmintrin.h>

namespace r {

	static const glm::ivec4 SIDES[] = {
		glm::ivec4(1, 0, 0, 0), glm::ivec4(0, 1, 0, 0), glm::ivec4(0, 0, 1, 0), // west, up, north
		glm::ivec4(-1, 0, 0, 0), glm::ivec4(0, -1, 0, 0), glm::ivec4(0, 0, -1, 0), // east, down, south 
	};

	struct Vertex {
		glm::vec3 pos;
		glm::vec2 uv;
	};

	Mesh::Mesh() {
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);
	}

	Mesh::~Mesh() {
		glDeleteBuffers(1, &ebo);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}

	bool Mesh::update(sh::Chunk &chunk) {
		auto world = chunk.world;
		const auto &palette = world->getPalette();

		std::vector<Vertex> data;

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
						glm::ivec4 pPos(x, y, -z, 0);
#endif
						glm::ivec3 pos(x, y, -z);

						// TODO: pointless but avx could vectorize this further
						for (int i = 0; i < SIDES->length(); i++) {
							const auto& side = SIDES[i];
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
							
							// TODO: check the solidity of blocks
							if (neighbor == sh::AIR_BLOCK) { 
								data.reserve(data.size() + 4); // 4 verts

								for (int j = 0; j < SIDES->length(); j++) {
									glm::vec3 pSide = side;
									glm::vec3 offset = SIDES[j];
									// TODO: there is a better way to do this, considering the SIDES table could be laid
									// out better
									if (glm::abs(pSide) == glm::abs(offset)) { continue; }
									data.push_back(Vertex {
										.pos = static_cast<glm::vec3>(pos) + glm::cross(pSide, offset) * 0.5f + pSide * 0.5f,
										.uv = glm::vec2()
									});	
								}
							}
						}
					}
				}
			}
		} catch (std::out_of_range& e) {
			std::cerr << e.what() << std::endl;
		}

		verts = data.size();

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), data.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
		
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, uv)));

		glBindVertexArray(0);

		return true;
	}

	bool Mesh::render() const {
		glBindVertexArray(vao);
		glDrawArrays(GL_LINES, 0, verts);
		glBindVertexArray(0);

		return true;
	}
} // r
