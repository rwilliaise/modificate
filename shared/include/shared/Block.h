
#pragma once

#include <functional>
#include <glm/ext/vector_int3.hpp>

namespace sh {

	struct Block {
		std::function<void (glm::ivec3)> placed;

	};

	struct BlockEntity {
		Block& block;
		glm::ivec3 pos;
	};
}
