
find_package(PkgConfig)

if (PKG_CONFIG_FOUND)
    pkg_check_modules(LUAJIT IMPORTED_TARGET luajit)
endif()

if (NOT LUAJIT_FOUND)
    externalproject_add(luajit_build
        URL                         https://luajit.org/download/LuaJIT-2.1.0-beta3.tar.gz
        URL_HASH                    SHA256=1ad2e34b111c802f9d0cdf019e986909123237a28c746b21295b63c9e785d9c3
        CONFIGURE_COMMAND           ""
        BUILD_COMMAND               ${MAKE_EXE} -C <SOURCE_DIR>
        INSTALL_COMMAND             ${MAKE_EXE} -C <SOURCE_DIR> install PREFIX=<INSTALL_DIR>
        DOWNLOAD_EXTRACT_TIMESTAMP  ON
    )

    externalproject_get_property(luajit_build INSTALL_DIR)
    add_library(luajit STATIC IMPORTED)
    set_target_properties(luajit PROPERTIES IMPORTED_LOCATION ${INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}luajit-5.1${CMAKE_STATIC_LIBRARY_SUFFIX})
    make_directory(${INSTALL_DIR}/include) # during configuration
    target_include_directories(luajit INTERFACE ${INSTALL_DIR}/include)
    unset(INSTALL_DIR)
endif()

add_library(modificate_luajit MODULE loader.c)
target_link_libraries(modificate_luajit PRIVATE modificate_interface)

if (LUAJIT_FOUND)
    target_link_libraries(modificate_luajit PRIVATE PkgConfig::LUAJIT)
else()
    target_link_libraries(modificate_luajit PRIVATE luajit)
    add_dependencies(modificate_luajit luajit_build)
endif()
