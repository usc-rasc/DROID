#include <iostream>
#include <set>
#include <queue>
#include <ontology/node.h>
#include <ontology/ontology.h>
#include <ontology/modinterface.h>

int main()
{
    Ontology ontology( std::cin );
    
    ModInterface current_interface; 
    ModInterface test_interface;
    
    int requirements_node_id = ontology.getRequirementsNodeID();
    Node requirements_node = ontology.getNode( requirements_node_id );
    
    current_interface.addModality( requirements_node );
    current_interface.print(); 
    current_interface.addModality( ontology.getNode( 18 ));
    current_interface.print(); 
    current_interface.addModality( ontology.getNode( 9 ) );
    current_interface.print(); 
    current_interface.addModality( ontology.getNode( 0 ) );
    current_interface.print(); 
    
    test_interface.addModality( requirements_node );
    test_interface.print(); 
    test_interface.addModality( ontology.getNode( 18 ) );
    test_interface.print(); 
    test_interface.addModality( ontology.getNode( 9 ) );
    test_interface.print(); 
    test_interface.addModality( ontology.getNode( 0 ) );
    test_interface.print(); 
    
    if( current_interface.compare( test_interface ) )
    {
   	    std::cout << "True!!!" << std::endl;
    }
    else
    {
        std::cout << "False!!!" << std::endl;
    }
    
    if( current_interface == test_interface )
    {
        std::cout << "True!!!" << std::endl;
    }
    else
    {
        std::cout << "False!!!" << std::endl;
    }
    
    return 0;
}
