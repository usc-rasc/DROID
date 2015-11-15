FILE( GLOB ontologies RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.ont )

set( ontology_dotfiles )
set( ontology_pdfs )

message( "${ontologies}" )

find_program( dot_executable_location "dot" )

foreach( ontology ${ontologies} )
	get_filename_component( ontology_name ${ontology} NAME_WE )
	message( "${ontology} -> ${ontology_name}.dot" )

	file( RELATIVE_PATH ontology_relpath ${PROJECT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/${ontology_name}" )
	file( RELATIVE_PATH dotfile_relpath ${PROJECT_SOURCE_DIR} "${CMAKE_CURRENT_BINARY_DIR}/${ontology_name}" )

	add_custom_command(
		OUTPUT "${ontology_name}.dot"
		COMMAND ${EXECUTABLE_OUTPUT_PATH}/ont2dot < "${ontology_relpath}.ont" > "${dotfile_relpath}.dot"
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		COMMENT "Generating graphviz for ${ontology}"
		DEPENDS ont2dot )
	list( APPEND ontology_dotfiles "${ontology_name}.dot" )

	add_custom_command(
		OUTPUT "${ontology_name}.pdf"
		COMMAND ${dot_executable_location} -Tpdf "${dotfile_relpath}.dot" -o "${dotfile_relpath}.pdf"
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		COMMENT "Generating graphviz for ${ontology}"
		DEPENDS "${ontology_name}.dot" )
	list( APPEND ontology_pdfs "${ontology_name}.pdf" )

endforeach()

message( "${ontology_dotfiles}" )
message( "${ontology_pdfs}" )
add_custom_target( ontology_graphviz ALL DEPENDS ${ontology_dotfiles} )
add_custom_target( ontology_pdfs DEPENDS ${ontology_pdfs} )
