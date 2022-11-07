
#pragma once

#include <memory>

namespace scr {

	class Vm {
	public:
		Vm();

		inline void *get() { 
			return state.get();
		}

	private:
		std::shared_ptr<void> state;
	};

} // scr
