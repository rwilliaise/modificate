
#ifndef MODIFICATE_INTERFACE_H_
#define MODIFICATE_INTERFACE_H_

#ifndef MODIFICATE_PLUGIN

#include <client/render.h>
#include <client/atlas.h>

#endif // MODIFICATE_PLUGIN

#include <shared/environment.h>
#include <shared/cmp.h>
#include <shared/log.h>
#include <shared/mod.h>
#include <shared/world.h>

#include <stdbool.h>

#if defined(__linux__)
#define MODEXPORT
#elif defined(_WIN32)
#define MODEXPORT __declspec(dllexport)
#endif

// These are functions you can define in your mod. Unexported functions are
// ignored by the game.

/**
 * Runs once when the mod loads. Doesn't always occur at game initialization.
 * The mod argument is the mod_t* representing your mod.
 */
MODEXPORT void mod_initialize(mod_t *mod);

// Mod loader functions
// See the modificate default luajit implementation for an example
// implementation of the loaders.

/**
 * Gauges whether or not a mod should be handled by this loader.
 */
MODEXPORT bool mod_loader_should_load(mod_t *loading_mod);
/**
 * Loads a mod
 */
MODEXPORT int mod_loader_load(mod_t *loading_mod);

#endif // MODIFICATE_INTERFACE_H_
