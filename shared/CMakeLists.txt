
set(SHARED_SOURCES
    src/Vm.cpp
)


add_library(shared STATIC ${SHARED_SOURCES})
target_include_directories(shared PUBLIC include/)
target_link_libraries(shared PUBLIC lua)

set_property(TARGET shared PROPERTY CXX_STANDARD 20)
set_property(TARGET shared PROPERTY CXX_STANDARD_REQUIRED ON)

if(MSVC)
	target_compile_options(shared PUBLIC /arch:SSE4.1)
else()
	target_compile_options(shared PUBLIC -msse4.1)
endif()

add_subdirectory(tests/lua/)
add_subdirectory(tests/mod/)

