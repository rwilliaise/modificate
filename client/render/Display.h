
#pragma once

#include "Render.h"

#include <GLFW/glfw3.h>
#include <memory>

namespace r {

	class Display {
	public:
		Display();

		inline bool shouldClose() {
			return glfwWindowShouldClose(window.get());
		}

		void poll();

	private: 
		std::shared_ptr<GLFWwindow> window;
	};

} // r
