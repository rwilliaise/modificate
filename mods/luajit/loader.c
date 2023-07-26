
#include <modificate/interface.h>

MODEXPORT bool mod_loader_should_load(mod_t *mod) {
    if (mod_path_exists(mod, "lua")) {
        return true;
    }
    return false;
}

MODEXPORT int mod_loader_load(mod_t *mod) {
    
    return 0;
}

