
#pragma once

#include <functional>
#include <glm/ext/vector_int3.hpp>

namespace sh {

	enum BlockEvent {
		BLOCK_EVENT_INIT,
		BLOCK_EVENT_PLACE,
		BLOCK_EVENT_BREAK,
		BLOCK_EVENT_USE,
	};

	struct Block {
		std::function<bool (glm::ivec3, BlockEvent)> event;
	};

	struct BlockEntity {
		Block& block;
		glm::ivec3 pos;
	};
}
