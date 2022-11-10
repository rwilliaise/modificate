
#pragma once

#include <functional>
#include <glm/ext/vector_int3.hpp>

namespace sh {

	struct Block {
		std::function<void (int)> stepped;

	};

	struct BlockEntity {
		Block& block;
		glm::ivec3 pos;
	};
}
