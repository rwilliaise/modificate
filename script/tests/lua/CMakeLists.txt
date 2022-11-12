

add_executable(test_expect expect.cpp)
target_link_libraries(test_expect PRIVATE script ${LUA_LIBRARIES})
target_include_directories(test_expect PRIVATE ${LUA_INCLUDE_DIRS})

function(expect EXPECTED_NAME EXPECTED_FILE)
	file(READ ${EXPECTED_FILE} READ_EXPECTED_FILE)
	add_test(NAME ${EXPECTED_NAME} COMMAND test_expect ${READ_EXPECTED_FILE})
endfunction()

expect("expect file loading" expect.lua)
expect("io.tmpfile usage" tmpfile.lua)
expect("Block: .new()" block.lua)


