
#include <shared/environment.h>
#include <shared/log.h>

#include <stdlib.h>

environment_t env_loaded = ENV_DEDICATED_SERVER;

void env_exit(int status) {
    exit(status);
}

int main(int argc, char *argv[]) {
    log_open();
}
