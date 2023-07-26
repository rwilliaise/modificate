
#ifndef SHARED_ENVIRONMENT_H_
#define SHARED_ENVIRONMENT_H_

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#define MODIFICATE_POSIX 1
#endif

#if defined(__linux__)
#define MODIFICATE_PLATFORM_LINUX 1
#elif defined(__APPLE__)
#define MODIFICATE_PLATFORM_MACOS 1
#elif define(_WIN32)
#define MODIFICATE_PLATFORM_WINDOWS 1
#endif

/**
 * Different states that the executable can be in. 
 */
typedef enum {
    ENV_DEDICATED_SERVER, // running a multiplayer listen server
    ENV_DEDICATED_CLIENT, // client listening to a server
    ENV_INTEGRATED_SERVER, // server running on the client so memory is shared
    ENV_UNCONNECTED_CLIENT, // a client unconnected 
} environment_t;

extern environment_t env_loaded;
extern char *env_running_directory;

void env_exit(int status);

#endif // SHARED_ENVIRONMENT_H_
