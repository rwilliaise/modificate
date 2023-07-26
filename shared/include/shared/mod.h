
#ifndef SHARED_MOD_H_
#define SHARED_MOD_H_

#include <stdint.h>

/**
 * Standardized permissions for all mods.
 */
typedef struct {
    uint8_t sys_access      : 1; // access filesystem and OS 
    uint8_t render_access   : 1; // access gui, rendering/gl context
    uint8_t world_access    : 1; // access world, add blocks, items, objects
} mod_security_t;

typedef struct mod {
    char *id;
    char *root_path;

    struct mod_loader {
        struct mod *loader;
        void *ud;
    } *loaders;
} mod_t;

// Mod loading occurs in two distinct phases: queuing, and loading. Queuing is
// where mods are detected and iterated through and loaders are chosen for each
// mod.

/**
 * Queues a mod for loading. root_path should be an absolute path.
 */
int mod_queue(char *root_path);
int mod_load_queue();

int mod_dll_loader_init();

/**
 * Checks if a path within a mod directory exists.
 */
int mod_path_exists(mod_t *mod, char *sub_path);

/**
 * Attach userdata associated with one mod (src) to another mod (dest).
 */
int mod_loader_attach(mod_t *dest, mod_t *src, void *ud);

#endif // SHARED_MOD_H_
