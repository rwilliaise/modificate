
#pragma once

#include <memory>
#include <vector>
#include <string>

namespace sh {

	class Vm {
	public:
		Vm();

		inline void *get() { 
			return state.get();
		}

		void open(std::vector<char> mem, std::string filename);
		void open(std::string mem, std::string filename);

	private:
		std::shared_ptr<void> state;
	};

} // sh
