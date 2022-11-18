
#pragma once

#include <functional>
#include <glm/ext/vector_int3.hpp>

namespace sh {

	struct Block {

	};

	struct BlockEntity {
		Block& block;
		glm::ivec3 pos;
	};
}
