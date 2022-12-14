
#include "render/Camera.h"
#include "render/Mesh.h"
#include "render/Display.h"
#include "render/Render.h"
#include <atomic>
#include <shared/Vm.h>

#include <filesystem>
#include <iostream>
#include <cstring>
#include <cctype>
#include <memory>
#include <string>
#include <thread>

struct Args {
	const char *modsFolder;
};

static void processArguments(Args &args, int argc, char *argv[]) {
	char state = ' ';
	for (int i = 1; i < argc; i++) {
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
}

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

	processArguments(args, argc, argv);

	auto modsFolderPath = std::filesystem::absolute(args.modsFolder);

	std::atomic_bool open = true;
	std::shared_ptr<sh::World> world = std::make_shared<sh::World>();
	sh::Vm vm(world);

	try {
		sh::loadMods(vm, modsFolderPath.string());
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	std::thread renderThread(&r::startRenderThread, world, open);
	std::thread vmThread(&sh::Vm::run, world, open, args.modsFolder);

	renderThread.join();

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
