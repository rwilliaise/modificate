
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
} // r
