
#include "render/Camera.h"
#include "render/Mesh.h"
#include "render/Display.h"
#include <shared/Vm.h>

#include <filesystem>
#include <iostream>
#include <cstring>
#include <cctype>
#include <memory>
#include <string>

struct Args {
	const char *modsFolder;

};

static inline int start(int argc, char *argv[]) {
	glfwSetErrorCallback([](int code, const char *desc) {
		std::cerr << "GLFW ERROR (" << code << "): " << desc << std::endl;
	});
	
	if (glfwInit() == GLFW_FALSE) {
		return 1;
	}


	Args args = {
		.modsFolder = "mods",
	};
	char state = ' ';
	for (int i = 0; i < argc; i++) {
		std::string arg(argv[i]);
		
		switch (state) {
		case 'm':
			state = ' ';
			args.modsFolder = argv[i];
			std::cout << "modsFolder = " << args.modsFolder << std::endl;
			break;
		}

		if (arg == "--mods" || arg == "-m") {
			state = 'm';
		}
	}

	auto modsFolderPath = std::filesystem::absolute(args.modsFolder);

	std::shared_ptr<sh::World> world = std::make_shared<sh::World>();
	sh::Vm vm(world);

	try {
		sh::loadMods(vm, modsFolderPath.string());
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	r::Display display;

	sh::Camera camera;
	);

	sh::Chunk testChunk;
	testChunk.world = world;
	testChunk.setBlock(glm::u8vec3(0, 0, 8), "test");

	r::Mesh testMesh;
	testMesh.update(testChunk);

	while (!display.shouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1, 0, 0, 1);

		testMesh.render();

		display.poll();
	}

	std::cout << "hi" << std::endl;

	return 0;
}

#ifdef _WIN32 
#include <windows.h>

int WinMain(HINSTANCE /* inst */,
			HINSTANCE /* preInst */,
			LPSTR args,
			int /* shown */) {

	size_t pos;
	std::vector<char *> argv;

	char state = ' ';
	char *word = args;
	char *curr;
	for (curr = args; *curr != 0; curr++) {
		switch (state) {
		case ' ':
			if (*curr == '"') {
				state = '"';
				word = ++curr;
			} else if (std::isspace(*curr)) {
				argv.push_back(word);
				*curr = 0;
				word = ++curr;
			}
			break;
		case '"':
			if (*curr == '"') {
				*curr = 0;
				curr += 2; // one space after the quote
				 
				argv.push_back(word);
				word = curr;

				state = ' ';
			}
			break;
		}
		
	}
	if (*curr == 0) {
		argv.push_back(word);
	}
	
	return start(argv.size(), argv.data());
}

#else

int main(int argc, char* argv[]) {
	return start(argc, argv);
}

#endif
