
#pragma once

#include <filesystem>

namespace sh {

    std::filesystem::path get_data_path();

    bool has_environment(const char *name);
    char *get_environment(const char *name);
}
