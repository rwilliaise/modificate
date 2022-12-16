
#include "Display.h"

namespace r {

	Display::Display() {
		GLFWwindow *win = glfwCreateWindow(640, 480, "modificate", nullptr, nullptr);

		glfwMakeContextCurrent(win);
		gladLoadGL(glfwGetProcAddress);

		glfwSetWindowUserPointer(win, this);

		glfwSetWindowSizeCallback(win, [](auto win, auto width, auto height) {
			Display *display = (Display *) glfwGetWindowUserPointer(win);
			
			if (display->sizeCallback) {
				display->sizeCallback(width, height);
			}
		});

		window = std::shared_ptr<GLFWwindow>(win, glfwDestroyWindow);
	}

	void Display::poll() {
		GLFWwindow *win = window.get();

		glfwSwapBuffers(win);
		glfwPollEvents();
	}

} // r
