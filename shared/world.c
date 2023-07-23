
#include <shared/environment.h>
#include <shared/log.h>
#include <shared/world.h>

world_t *loaded_world = NULL;

void world_load() {
    if (loaded_world) {
        log_log(LOG_WARN, "world already loaded!");
        return;
    }
    loaded_world = malloc(sizeof(world_t));

    switch(loaded_env) {
    case ENV_DEDICATED_SERVER:
        
    case ENV_INTEGRATED_SERVER:

        break;
    default:
        break;
    }
}

