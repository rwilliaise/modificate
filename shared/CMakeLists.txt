
set(SHARED_SOURCES
	src/lua/LuaVm.cpp
	src/lua/LuaWorld.cpp
	src/lua/LuaVector.cpp
	src/lua/Mod.cpp
	src/Chunk.cpp
	src/Tar.cpp
	src/World.cpp
)


add_library(shared STATIC ${SHARED_SOURCES})
target_include_directories(shared PUBLIC include/)
target_link_libraries(shared PUBLIC lua)

set_property(TARGET shared PROPERTY CXX_STANDARD 17)
set_property(TARGET shared PROPERTY CXX_STANDARD_REQUIRED ON)

add_subdirectory(tests/lua/)
add_subdirectory(tests/mod/)

