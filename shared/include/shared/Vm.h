
#pragma once

#include <atomic>
#include <memory>
#include <vector>
#include <string>

#include "World.h"
#include "Mod.h" 

namespace sh {

	/**
	 * Intentionally opaque class to allow multiple backends.
	 */
	class Vm {
	public:
		explicit Vm(std::shared_ptr<World> world);

		inline void *get() { 
			return global.get();
		}

		inline auto getWorld() { 
			return world;
		}

		inline const auto& getMods() {
			return mods;
		}

		/**
		 * Split global context into another smaller context (mod).
		 */
		void split(Mod &&mod);
		void split(Mod &mod);

		void run(std::atomic_bool &, std::string &folderName);
		void loadFolder(std::string folderName);

	private:
		std::shared_ptr<void> global;
		std::shared_ptr<World> world;

		std::vector<Mod> mods;
	};

} // sh


