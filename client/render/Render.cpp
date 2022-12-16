
#include "Render.h"
#include "Camera.h"
#include "Display.h"
#include "Mesh.h"

#include "shared/World.h"

#include <memory>

namespace r {

	void startRenderThread(std::shared_ptr<sh::World> world, std::atomic_bool *open) {
		r::Display display;

		sh::Camera camera;

		display.setSizeCallback([&](auto width, auto height) {
			camera.updateProjection(width, height);
			glViewport(0, 0, width, height);
		});

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

		open->store(false, std::memory_order_release);
	}
} // r

