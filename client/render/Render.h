
#pragma once

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
