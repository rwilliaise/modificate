
#include "LuaVector.h"

#include <iostream>
#include <glm/geometric.hpp>

#define BINARY_OP(op) [](lua_State *L) { 	\
	glm::vec3 v1 = getVector(L, 1); 		\
	glm::vec3 v2 = getVector(L, 2); 		\
	op 										\
	return 1; 								\
}

#define UNARY_OP(op) [](lua_State *L) { 	\
	glm::vec3 v1 = getVector(L, 1); 		\
	op 										\
	return 1; 								\
}
namespace sh {
	
	static const char *VECTOR_METATABLE = "vector";

	static int toStringVector(lua_State *L) {
		glm::vec3 v1 = getVector(L, 1);
		lua_pushfstring(L, "vec [%f, %f, %f]", v1.x, v1.y, v1.z);

		return true;
	}

	static const luaL_Reg vectorMetaMethods[] = {
		// {"__index", nullptr}, TODO: dot, cross product
		{"__tostring", toStringVector},
		{"__add", BINARY_OP({
			pushVector(L, v1 + v2);
		})},
		{"__sub", BINARY_OP({
			pushVector(L, v1 - v2);
		})},
		{"__mul", BINARY_OP({
			pushVector(L, v1 * v2);
		})},
		{"__div", BINARY_OP({
			pushVector(L, v1 / v2);
		})},
		{"__idiv", BINARY_OP({
			pushVector(L, static_cast<glm::ivec3>(v1 / v2));
		})},
		{"__eq", BINARY_OP({
			lua_pushboolean(L, v1 == v2);
		})},
		{"__unm", UNARY_OP({
			pushVector(L, -v1);
		})},
		{"__len", UNARY_OP({
			lua_pushnumber(L, glm::length(v1));
		})},
		{nullptr, nullptr},
	};

	static const luaL_Reg vectorMethods[] = {
		{"dot", BINARY_OP({
			lua_pushnumber(L, glm::dot(v1, v2));
		})},
		{"distance", BINARY_OP({
			lua_pushnumber(L, glm::distance(v1, v2));
		})},
		{"cross", BINARY_OP({
			pushVector(L, glm::cross(v1, v2));
		})},
		{"normalize", UNARY_OP({
			pushVector(L, glm::normalize(v1));
		})},
		{"length", UNARY_OP({
			lua_pushnumber(L, glm::length(v1));
		})},
		{nullptr, nullptr},
	};

	glm::vec3 getVector(lua_State *L, int idx) {
		if (lua_type(L, idx) != LUA_TTABLE && lua_type(L, idx) != LUA_TNUMBER) {
			luaL_error(L, "got %s, expected vector or number", lua_typename(L, lua_type(L, idx)));
		}
		if (lua_type(L, idx) == LUA_TTABLE) {
			lua_getfield(L, idx, "x");
			lua_getfield(L, idx, "y");
			lua_getfield(L, idx, "z");

			glm::vec3 out(lua_tonumber(L, -3), lua_tonumber(L, -2), lua_tonumber(L, -1));

			lua_pop(L, 3);
			return out;
		}

		float num = lua_tonumber(L, idx);
		glm::vec3 out(num, num, num);
		return out;
	}

	glm::ivec3 getVectori(lua_State *L, int idx) {
		return static_cast<glm::ivec3>(getVector(L, idx));
	}

	void pushVector(lua_State *L, glm::vec3 vec) {
		lua_newtable(L);
		luaL_setmetatable(L, VECTOR_METATABLE);

		lua_pushnumber(L, vec.z);
		lua_pushnumber(L, vec.y);
		lua_pushnumber(L, vec.x);

		lua_setfield(L, -4, "x");
		lua_setfield(L, -3, "y");
		lua_setfield(L, -2, "z");

	}

	void pushVector(lua_State *L, glm::ivec3 vec) {
		pushVector(L, glm::vec3(vec.x, vec.y, vec.z));
	}

	void pushVector(lua_State *L) {
		pushVector(L, glm::vec3());
	}

	static int newVector(lua_State *L) { 
		if (lua_isnumber(L, 1)) {
			float x, y, z;
			x = luaL_checknumber(L, 1);
			y = luaL_checknumber(L, 2);
			z = luaL_checknumber(L, 3);

			pushVector(L, glm::vec3(x, y, z));

			return true;
		}

		pushVector(L, glm::vec3());
		
		return true;
	}

	static const luaL_Reg vectorLib[] = {
		{"vector", newVector},
		{nullptr, nullptr},
	};

	static int createVectorMetatable(lua_State *L) {
		luaL_newmetatable(L, VECTOR_METATABLE);
		luaL_setfuncs(L, vectorMetaMethods, 0);

		lua_pushliteral(L, "vector");
		lua_setfield(L, -2, "__name");

		luaL_newlib(L, vectorMethods);
		lua_setfield(L, -2, "__index");

		lua_pushstring(L, VECTOR_METATABLE);
		lua_setfield(L, -2, "__metatable");

		return true;
	}

	static int mountVectorLib(lua_State *L) {
		createVectorMetatable(L);

		lua_pushglobaltable(L);
		luaL_setfuncs(L, vectorLib, 0);
		lua_pop(L, -1);

		return true;
	}

	void openVectorLib(lua_State *L) {
		luaL_requiref(L, LIB_VECTORNAME, mountVectorLib, false);
		lua_pop(L, -1);
	}
} // sh
