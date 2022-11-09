
#include "glad/gl.h"
#include "render/Display.h"
#include <GLFW/glfw3.h>
#include <iostream>

static inline int start() {
	glfwSetErrorCallback([](int code, const char *desc) {
		std::cerr << "GLFW ERROR (" << code << "): " << desc << std::endl;
	});
	
	if (glfwInit() == GLFW_FALSE) {
		return 1;
	}

	r::Display display;

	while (!display.shouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1, 0, 0, 1);

		display.poll();
	}

	return 0;
}

#ifdef _WIN32 
#include <winbase.h>

int WinMain(HINSTANCE /* inst */,
			HINSTANCE /* preInst */,
			PWSTR /* args */,
			int /* shown */) {
	return start();
}

#else

int main(int argc, char* argv[]) {
	return start();
}

#endif
