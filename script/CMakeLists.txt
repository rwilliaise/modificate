
set(SCRIPT_SOURCES
	src/lua/LuaVm.cpp
	src/Tar.cpp
)

find_package(Lua REQUIRED)

add_library(script STATIC ${SCRIPT_SOURCES})
target_include_directories(script PUBLIC include/ PRIVATE ${LUA_INCLUDE_DIRS})
target_link_libraries(script PUBLIC world PRIVATE ${LUA_LIBRARIES})

add_subdirectory(tests/lua)
add_subdirectory(tests/mod)

