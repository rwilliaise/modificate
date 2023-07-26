
add_library(modificate_shared
    log.c
    cmp.c
)
target_include_directories(modificate_shared SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(modificate_shared PUBLIC ${CMAKE_DL_LIBS}
    Threads::Threads cglm m LibArchive::LibArchive)
link_libraries()
