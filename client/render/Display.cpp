
#include "Display.h"
#include "glad/gl.h"
#include <GLFW/glfw3.h>

namespace r {

	Display::Display() {
		GLFWwindow *win = glfwCreateWindow(640, 480, "modificate", nullptr, nullptr);

		glfwMakeContextCurrent(win);
		gladLoadGL(glfwGetProcAddress);

		window = std::shared_ptr<GLFWwindow>(win, glfwDestroyWindow);
	}

	void Display::poll() {
		GLFWwindow *win = window.get();

		glfwSwapBuffers(win);
		glfwPollEvents();
	}

} // r
