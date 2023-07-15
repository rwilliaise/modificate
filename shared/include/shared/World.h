
#pragma once

#include "shared/Level.h"

#include <map>
#include <memory>
#include <string>

namespace sh {
    
    class World : public std::enable_shared_from_this<World> {
    public:

        explicit World (std::filesystem::path world_path): world_path(world_path) {}

        World(World &&) = default;
        World &operator=(World &&) = default;
        World(const World &) = delete;
        World &operator=(const World &) = delete;

    private:
        std::filesystem::path world_path;
        std::map<std::string, Level> levels;
    };
}
