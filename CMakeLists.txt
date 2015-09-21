cmake_minimum_required(VERSION 2.4.6)

project( ontology )

set( CMAKE_BUILD_TYPE Release )

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory( src )
add_subdirectory( exe )
add_subdirectory( shared )
