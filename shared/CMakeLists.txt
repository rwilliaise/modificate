
set(SHARED_SOURCES
	src/lua/LuaVm.cpp
	src/lua/Mod.cpp
	src/Chunk.cpp
	src/Tar.cpp
	src/World.cpp
)

add_library(shared STATIC ${SHARED_SOURCES})
target_include_directories(shared PUBLIC include/)
target_link_libraries(shared PUBLIC lua)

