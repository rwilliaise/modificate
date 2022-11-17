
#include "shared/World.h"
#include <lua.hpp>

namespace sh {

	/**
	 * The world library can be alternatively accessed with `require('world')`.
	 */
	constexpr const char *LIB_WORLDNAME = "world";

	void openWorldLib(lua_State *L, std::shared_ptr<World> world);
} // sh
