
set(CLIENT_SOURCES
	main.cpp

	# render
	render/Display.cpp
)

find_package(glfw3 REQUIRED)

if(WIN32)
	add_executable(client WIN32 ${CLIENT_SOURCES})
elseif(APPLE)
	add_executable(client MACOSX_BUNDLE ${CLIENT_SOURCES})
else()
	add_executable(client ${CLIENT_SOURCES})
endif()

target_link_libraries(client PRIVATE glfw glad)

