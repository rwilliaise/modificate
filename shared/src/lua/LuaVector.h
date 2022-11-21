
#pragma once

#include <glm/vec3.hpp>
#include <lua.hpp>

namespace sh {

	constexpr const char *LIB_VECTORNAME = "vector";

	void openVectorLib(lua_State *L);

	glm::vec3 getVector(lua_State *L, int idx);
	glm::ivec3 getVectori(lua_State *L, int idx);

	void pushVector(lua_State *L);
	void pushVector(lua_State *L, glm::vec3 vec);
	void pushVector(lua_State *L, glm::ivec3 vec);
} // sh
