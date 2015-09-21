FILE( GLOB executables RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp )

foreach( executable ${executables} )
	get_filename_component( executable_name ${executable} NAME_WE )
	include_directories( ${PROJECT_SOURCE_DIR}/include )
	add_executable( ${executable_name} ${executable} )
	target_link_libraries( ${executable_name} ${PROJECT_NAME} )
endforeach()
