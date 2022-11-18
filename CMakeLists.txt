cmake_minimum_required(VERSION 3.21)
project(modificate C CXX)

set(CXX_STANDARD 17)

enable_testing()

include(AddMod.cmake)

find_package(glm REQUIRED)
find_package(Boost 1.80 REQUIRED COMPONENTS
			 json)

link_libraries(glm)
link_libraries(Boost::json)

# Personally, I use clangd which the only way to make compatible is to forcefully
# include the MSYS dirs. Either that or put up with vcpkg.
if(WIN32 AND NOT VCPKG_TARGET_TRIPLET) # no vcpkg installed
	execute_process(COMMAND uname -s OUTPUT_VARIABLE SYS_NAME)
	find_package(Msys)
	if (MSYS OR SYS_NAME MATCHES "^MSYS" OR SYS_NAME MATCHES "^MINGW")
		message(STATUS "MSYS detected, using MSYS include dirs")
		set(MSYS_ENV $ENV{MSYSTEM})
		include_directories("${MSYS_INSTALL_PATH}/${MSYS_ENV}/include")
		add_compile_options(-target x86_64-pc-windows-gnu)
	endif()
endif()

add_subdirectory(thirdparty/lua)
add_subdirectory(thirdparty/glad)

add_subdirectory(shared)
add_subdirectory(client)

