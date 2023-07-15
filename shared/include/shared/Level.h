
#pragma once

#include <cstdint>
#include <filesystem>
#include <glm/ext/vector_int3.hpp>
#include <glm/ext/vector_uint3_sized.hpp>
#include <memory>
#include <unordered_map>

namespace sh {

    const uint8_t CHUNK_SIZE = 16;

    class Chunk {
    public:

        inline auto getBlock(glm::u8vec3 pos) const {
            return blocks[pos.x][pos.y][pos.z];
        }

    private:
        uint16_t blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    };
    
    class Level {
    public:

        explicit Level(std::filesystem::path level_path): level_path(level_path) {}

        Level(Level &&) = default;
        Level &operator=(Level &&) = default;
        Level(const Level &) = delete;
        Level &operator=(const Level &) = delete;

        std::string getBlock();

    private:
        std::filesystem::path level_path;
        std::unordered_map<uint16_t, std::string> palette;
        std::unordered_map<glm::ivec3, Chunk> chunks = std::unordered_map<glm::ivec3, Chunk>();
    };
}

