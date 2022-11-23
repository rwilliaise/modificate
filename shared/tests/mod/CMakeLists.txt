
add_executable(test_unpack unpack.cpp)
target_link_libraries(test_unpack PRIVATE shared)

add_executable(test_loading loading.cpp)
target_link_libraries(test_loading PRIVATE shared)

add_test(NAME "tar vfs unpack" COMMAND test_unpack "${CMAKE_CURRENT_LIST_DIR}/tar/mod.tar")
add_test(NAME "loading tar" COMMAND test_loading "${CMAKE_CURRENT_LIST_DIR}/tar/")

