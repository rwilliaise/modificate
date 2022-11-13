
set(SCRIPT_SOURCES
	src/lua/LuaVm.cpp
	src/lua/LibBlock.cpp
	src/Tar.cpp
)

add_library(script STATIC ${SCRIPT_SOURCES})
target_include_directories(script PUBLIC include/)
target_link_libraries(script PUBLIC world PRIVATE lua)

add_mod(src/lua/base/)

add_subdirectory(tests/lua)
add_subdirectory(tests/mod)

