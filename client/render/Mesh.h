
#pragma once

#include <shared/Chunk.h>

#include "Render.h"

namespace r {

	class Mesh {
	public:
		Mesh();
		~Mesh();
	
		// move only
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;
		Mesh(Mesh&&) = default;
		Mesh& operator=(Mesh&&) = default;

		bool update(sh::Chunk& chunk);
		bool render() const;

	private:
		size_t verts;

		GLuint vao;
		GLuint vbo;
		GLuint ebo;
	};
} // r
