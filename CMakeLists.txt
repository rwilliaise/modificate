cmake_minimum_required(VERSION 3.21)
project(modificate C CXX)

set(CXX_STANDARD 17)

enable_testing()

add_subdirectory(thirdparty/glad)

add_subdirectory(world)
add_subdirectory(script)

add_subdirectory(client)

