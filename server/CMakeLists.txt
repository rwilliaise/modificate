
add_executable(modificate_server
    server.c
)
target_link_libraries(modificate_server PRIVATE modificate_shared)

