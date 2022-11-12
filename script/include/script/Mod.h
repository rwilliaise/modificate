
#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "world/World.h"

namespace sh {

	/**
	 * Represents one mod.
	 */
	class Mod {
	public:

		Mod() = default;
		Mod(const Mod&) = delete;
		Mod(Mod&&) = default;
		Mod& operator=(const Mod&) = delete;
		Mod& operator=(Mod&&) = default;

		/** 
		 * Mounts to a given world. Expects vfs to be full. 
		 */
		void mount(World& world);
		void tar_loadFromMemory(std::vector<char> mem);

		std::unordered_map<std::string, std::vector<char>> vfs;

	private:
	};
}
