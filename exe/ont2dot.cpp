#include <iostream>
#include <set>
#include <queue>

#include <ontology/node.h>
#include <ontology/ontology.h>

void printHelp()
{
    std::cout << "ont2dot [options] < input.ont > output.dot" << std::endl;
    std::cout << "-h, --help | this help menu" << std::endl;
}

int main( int argc, char ** argv )
{
    for( int i = 1; i < argc; ++i )
    {
        std::string const arg( argv[i] );

        if( arg == "-h" || arg == "--help" )
        {
            printHelp();
            return 0;
        }

        std::cerr << "Unrecognized option: " << argv[i] << std::endl;
    }

    Ontology ontology( std::cin );

//  ontology.printOntology();

//  std::string const input_filename( argv[i] );
//
//  size_t const extension_idx = input_filename.find_last_of( "." + Ontology::getFileExtension() );
//  if( extension_idx == std::string::npos )
//  {
//      std::cout << "Error: expected filename with extension ." + Ontology::getFileExtension() << std::endl;
//      return 1;
//  }
//
//  std::string const filename_base = input_filename.substr( 0, extension_idx );
//
//  ontology.printDotFile( filename_base + ".dot" );

    ontology.printDotFile( std::cout );
}
