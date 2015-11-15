FILE( GLOB ontologies RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.ont )

set( ontology_dotfiles )

message( "${ontologies}" )

foreach( ontology ${ontologies} )
	get_filename_component( ontology_name ${ontology} NAME_WE )
	message( "${ontology} -> ${ontology_name}.dot" )

	add_custom_command(
		OUTPUT ${ontology_name}.dot
		COMMAND ${EXECUTABLE_OUTPUT_PATH}/ont2dot "${ontology}"
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "Generating graphviz for ${ontology}"
		DEPENDS ont2dot )

	list( APPEND ontology_dotfiles ${ontology_name}.dot )
endforeach()

message( "${ontology_dotfiles}" )
add_custom_target( ontology_graphviz ALL DEPENDS ${ontology_dotfiles} )
