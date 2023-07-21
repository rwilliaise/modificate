
externalproject_add(luajit
    URL                         https://luajit.org/download/LuaJIT-2.1.0-beta3.tar.gz
    URL_HASH                    SHA256=1ad2e34b111c802f9d0cdf019e986909123237a28c746b21295b63c9e785d9c3
    CONFIGURE_COMMAND           ""
    BUILD_COMMAND               ${MAKE_EXE} -C <SOURCE_DIR>
    INSTALL_COMMAND             ${MAKE_EXE} -C <SOURCE_DIR> install PREFIX=<INSTALL_DIR>
    DOWNLOAD_EXTRACT_TIMESTAMP  ON
)

externalproject_get_property(luajit INSTALL_DIR)
add_library(luajit_lib STATIC IMPORTED)
set_target_properties(luajit_lib PROPERTIES IMPORTED_LOCATION ${INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}luajit-5.1${CMAKE_STATIC_LIBRARY_SUFFIX})
make_directory(${INSTALL_DIR}/include) # during configuration
target_include_directories(luajit_lib INTERFACE ${INSTALL_DIR}/include)
unset(INSTALL_DIR)

add_library(modificate_shared
    log.c
    cmp.c
)
target_include_directories(modificate_shared SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(modificate_shared PRIVATE luajit_lib)
add_dependencies(modificate_shared luajit)
