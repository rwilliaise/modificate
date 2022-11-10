
#include <world/World.h>

namespace sh {

	bool World::setBlock(glm::ivec3 pos, std::string id) {
		glm::i16vec3 cpos = pos / CHUNK_SIZE;
		glm::u8vec3 crpos = pos % CHUNK_SIZE;
		auto chunk = chunks.find(cpos);
		if (chunk == chunks.end()) { // TODO: load chunk
			return false;
		}
		chunk->second.setBlock(crpos, id);
		return false;
	}

} // sh 
