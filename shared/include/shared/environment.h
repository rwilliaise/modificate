
#ifndef SHARED_ENVIRONMENT_H_
#define SHARED_ENVIRONMENT_H_

/**
 * Different states that the executable can be in. 
 */
typedef enum {
    ENV_DEDICATED_SERVER, // running a multiplayer listen server
    ENV_DEDICATED_CLIENT, // client listening to a server
    ENV_INTEGRATED_SERVER, // server running on the client so memory is shared
    ENV_UNCONNECTED_CLIENT, // a client unconnected 
} environment_t;

extern environment_t loaded_env;
extern char *fs_running_directory;

#endif // SHARED_ENVIRONMENT_H_
