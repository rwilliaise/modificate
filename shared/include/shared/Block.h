
#pragma once

#include <glm/ext/vector_int3.hpp>
#include <functional>
#include <memory>

namespace sh {
	class Mod;

	using BasicPositionedEvent = std::function<bool (Mod&, glm::ivec3)>;

	enum BlockEvent {
		BLOCK_EVENT_INIT,
		BLOCK_EVENT_PLACE,
		BLOCK_EVENT_BREAK,
		BLOCK_EVENT_USE,
	};

	struct Block {
		std::function<void (Mod&)> init;

		BasicPositionedEvent use;
		BasicPositionedEvent place;
		BasicPositionedEvent break_;
	};

	struct BlockEntity {
		Block& block;
		glm::ivec3 pos;
	};
}

