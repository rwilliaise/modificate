
#pragma once

#include <memory>
#include <vector>
#include <string>

#include <world/World.h>

namespace sh {

	/**
	 * Intentionally opaque class to allow multiple backends.
	 */
	class Vm {
	public:
		explicit Vm(std::shared_ptr<World> world);

		inline void *get() { 
			return state.get();
		}

		/**
		 * Runs a given chunk of memory. `filename` is used for debugging.
		 */
		bool open(std::vector<char> mem, std::string filename);
		bool open(std::string mem, std::string filename);

	private:
		std::shared_ptr<void> state;
		std::shared_ptr<World> world;
	};

} // sh


