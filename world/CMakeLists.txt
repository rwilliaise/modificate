
add_library(world STATIC src/Chunk.cpp)
target_include_directories(world SYSTEM PUBLIC include/)
target_link_libraries(world PRIVATE script)
