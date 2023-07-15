cmake_minimum_required(VERSION 3.21)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(modificate C CXX)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

include(cmake/AddMod.cmake)

find_package(glm CONFIG REQUIRED)
find_package(Boost 1.80 CONFIG REQUIRED COMPONENTS
			 json)
find_package(glfw3 CONFIG REQUIRED)

link_libraries(glm::glm)
link_libraries(Boost::json)

add_subdirectory(thirdparty/lua)
add_subdirectory(thirdparty/glad)

add_subdirectory(shared)
add_subdirectory(client)

include(cmake/Packaging.cmake)

