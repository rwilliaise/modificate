
add_executable(test_unpack unpack.cpp)
target_link_libraries(test_unpack PRIVATE script)

add_test(NAME "tar vfs unpack" COMMAND test_unpack "${CMAKE_CURRENT_LIST_DIR}/tar/mod.tar")

