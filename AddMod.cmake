
function(add_mod directory)
	file(RELATIVE_PATH src_dir ${CMAKE_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/${directory}")
	get_filename_component(directory_name ${src_dir} NAME)

	set(out_archive "${CMAKE_BINARY_DIR}/${directory_name}.tar")
	add_custom_command(OUTPUT "${directory_name}_mod" 
		COMMAND ${CMAKE_COMMAND} -E tar cv ${out_archive} .
		WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${directory}
		DEPENDS ${src_dir}
		COMMENT "Packing mod ${directory_name}"
		VERBATIM
	)
endfunction()
