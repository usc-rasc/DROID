FILE( GLOB src_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp )

include_directories( ${PROJECT_SOURCE_DIR}/include )
add_library( ${PROJECT_NAME} SHARED ${src_files} )
