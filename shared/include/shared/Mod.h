
#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

#include "World.h"

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
		bool mount(std::shared_ptr<World> world);

		/**
		 * Runs a given chunk of memory. `filename` is used for debugging.
		 */
		bool open(std::vector<char> mem, std::string filename);
		bool open(std::string mem, std::string filename);

		void tar_loadFromMemory(std::vector<char> mem);

		inline void *get() {
			return context.get();
		}

		std::unordered_map<std::string, std::vector<char>> vfs;

	private:
		friend class Vm;
		
		std::shared_ptr<void> context;
	};
}
