
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

int mod_queue(char *root_path) { 
    if (root_path == NULL) { return 1; }
    if (strlen(root_path) > PATH_MAX) { return 1; }

    return 0;
}

int mod_path_exists(mod_t *mod, char *sub_path) { 
    if (sub_path == NULL) { return 0; }
    size_t root_path_len = strlen(mod->root_path);
    size_t sub_path_len = strlen(sub_path);
    if (root_path_len + sub_path_len + 2 > PATH_MAX) { return 0; } // one for \0
                                                                   // and one
                                                                   // for /
    char path[PATH_MAX];
    strcpy(path, mod->root_path);
    path[root_path_len] = '/';
    strcpy(&path[root_path_len + 1], sub_path);

#if defined(MODIFICATE_POSIX)
    struct stat buf;
    stat(path, &buf);
    
    
#elif defined(MODIFICATE_PLATFORM_WINDOWS)
    // TODO
#endif

    return 0;
}

