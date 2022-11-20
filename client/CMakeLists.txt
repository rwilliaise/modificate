
set(CLIENT_SOURCES
	main.cpp

	# render
	render/Display.cpp
	render/Mesh.cpp
)

if(WIN32)
	add_executable(client WIN32 ${CLIENT_SOURCES})
elseif(APPLE)
	add_executable(client MACOSX_BUNDLE ${CLIENT_SOURCES})
else()
	add_executable(client ${CLIENT_SOURCES})
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	target_link_options(client PRIVATE -static-libgcc -static-libstdc++)
endif()

target_link_libraries(client PRIVATE glfw glad shared)

