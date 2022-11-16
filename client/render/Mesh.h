
#pragma once

#include <world/Chunk.h>

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

	private:
		GLuint vao;
		GLuint buffers[3];
	};
} // r