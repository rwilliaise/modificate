
#pragma once

#include <glm/ext/vector_int3.hpp>
#include <functional>
#include <memory>

namespace sh {
	class Mod;

	using BasicPositionedEvent = std::function<bool (Mod&, glm::ivec3)>;

	struct Block {
		BasicPositionedEvent use;
		BasicPositionedEvent place;
		BasicPositionedEvent break_;
	};

	struct BlockEntity {
		Block& block;
		glm::ivec3 pos;
	};
}

