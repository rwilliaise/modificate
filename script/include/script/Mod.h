
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

		Mod(const Mod&) = delete;
		Mod& operator=(const Mod&) = delete;

		/** 
		 * Mounts to a given world. Expects vfs to be full. 
		 */
		void mount(World& world);
		void tar_loadFromMemory(std::vector<char> mem);

		std::unordered_map<std::string, std::vector<char>> vfs;

	private:
	};
}
