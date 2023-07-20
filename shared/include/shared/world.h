
#ifndef SHARED_WORLD_H_
#define SHARED_WORLD_H_

#include <cglm/ivec3.h>

#define CHUNK_SIZE 16

typedef enum {
    NORTH,
    SOUTH,
    WEST,
    EAST,
    UP,
    DOWN,
} world_direction_t;

typedef struct {
    char *id; // block namespaced id, e.g. modificate:stone
    struct blockstate_values {
        char *id; // blockstate namespaced id, e.g. modificate:powered
        int value;
    } keys[0];
} world_blockstate_t;

/**
 * Loaded chunk in memory.
 */
typedef struct {
    ivec3 chunk_position;
    char blocks[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
    /* palette of block states used for the blocks array */
    world_blockstate_t *block_table[0];
} world_chunk_t;

typedef struct {
    world_chunk_t **chunks; // array of chunks
    int loaded_chunks;
} world_t;

extern world_t *loaded_world;

/**
 * This function shall load the world, and set the global loaded_world variable
 * with the output.
 *
 * This function shall behave differently across different environments:
 * On ENV_DEDICATED_SERVER and ENV_INTEGRATED_SERVER -> loads the world from
 * file, however if there is no save it loads a new empty world.
 * On ENV_DEDICATED_CLIENT -> loads a new empty world. Chunks should load in at
 * the connected servers discretion.
 * On ENV_UNCONNECTED_CLIENT -> undefined behavior.
 */
void world_load();
/**
 * This function shall save the world to file.
 *
 * This function shall behave differently across different environments:
 * On ENV_DEDICATED_SERVER and ENV_INTEGRATED_SERVER -> saves the world to file.
 * On ENV_INTEGRATED_SERVER and ENV_UNCONNECTED_CLIENT -> nothing.
 */
void world_save();

world_chunk_t *world_chunk_load(ivec3 chunk_position);

#endif // SHARED_WORLD_H_
