
#include <atomic>
#include <iostream>
#include <shared/Vm.h>

namespace sh {

	void Vm::run(std::atomic_bool &open, std::string &modFolder) {
		try {
			sh::loadMods(*this, modFolder);
		} catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
			open.store(false, std::memory_order_release);
		}
	}
} // sh
