
#pragma once

#include "shared/World.h"
#include <atomic>

#if defined(__i386__) || defined(__x86_64__)
#define R_SIMD_ENABLED

extern "C" {

#include <x86intrin.h>
#include <nmmintrin.h>

}
#endif

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace r {

	void startRenderThread(std::shared_ptr<sh::World>, std::atomic_bool *);
} // r
