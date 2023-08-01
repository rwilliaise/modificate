
#include <linux/limits.h>
#include <shared/environment.h>
#include <shared/mod.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#if defined(MODIFICATE_POSIX)
#include <sys/stat.h>
#elif defined(MODIFICATE_PLATFORM_WINDOWS)
// TODO
#endif

static char *mod_sub_path_safe(mod_t *mod, char *sub_path) {
    if (sub_path == NULL) { return NULL; }
    size_t root_path_length = strlen(mod->root_path);
    size_t sub_path_length = strlen(sub_path);
    if (root_path_length + sub_path_length + 2 > PATH_MAX) { return NULL; }
    
    char path[PATH_MAX];
    strcpy(path, mod->root_path);
    strcat(path, "/");
    strcat(path, sub_path);

    char *resolved = realpath(path, NULL);
    if (strncmp(mod->root_path, resolved, root_path_length) != 0) {
        free(resolved);
        return NULL;
    }
    return resolved;
}

int mod_queue(char *root_path) { 
    if (root_path == NULL) { return 1; }
    if (strlen(root_path) > PATH_MAX) { return 1; }



    return 0;
}

int mod_path_exists(mod_t *mod, char *sub_path) { 
    char *path = mod_sub_path_safe(mod, sub_path);
    if (path == NULL) { return 0; }

#if defined(MODIFICATE_POSIX)
    
#elif defined(MODIFICATE_PLATFORM_WINDOWS)
    // TODO
#endif
    free(path);

    return 0;
}

