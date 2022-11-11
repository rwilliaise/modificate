
#pragma once

#include <vector>
#include <string>
#include <unordered_map>

namespace sh {

	/**
	 * Represents one mod.
	 */
	class Mod {
	public:

		void tar_loadFromMemory(std::vector<char> mem);
		std::unordered_map<std::string, std::vector<char>> vfs;

	private:
	};
}
