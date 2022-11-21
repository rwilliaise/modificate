
add_executable(test_expect expect.cpp)
target_link_libraries(test_expect PRIVATE shared ${LUA_LIBRARIES})
target_include_directories(test_expect PRIVATE ${LUA_INCLUDE_DIRS})

function(expect EXPECTED_NAME EXPECTED_FILE)
	file(REAL_PATH ${EXPECTED_FILE} REAL_EXPECTED_FILE)
	add_test(NAME ${EXPECTED_NAME} COMMAND test_expect "${REAL_EXPECTED_FILE}")
endfunction()

expect("expect file loading" expect.lua)
expect("Block: .new()" block.lua)
expect("Vector math" vector.lua)


