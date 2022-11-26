
#include "Mesh.h"

#include <glad/gl.h>

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
		const auto &palette = chunk.getWorld();
		
#ifdef R_SIMD_ENABLED
		// TODO
#else

#endif

		return true;
	}
} // r
