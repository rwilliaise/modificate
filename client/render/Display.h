
#pragma once

#include "Render.h"

#include <GLFW/glfw3.h>
#include <functional>
#include <memory>

namespace r {

	class Display {
	public:
		Display();
		
		inline auto get() { return window.get(); }

		inline bool shouldClose() {
			return glfwWindowShouldClose(window.get());
		}

		inline void setSizeCallback(std::function<void (int, int)> cb) {
			sizeCallback = cb;

			int width, height;
			glfwGetWindowSize(get(), &width, &height);
			sizeCallback(width, height);
		}

		void poll();

	private: 
		std::shared_ptr<GLFWwindow> window;
		std::function<void (int, int)> sizeCallback;
	};

} // r
