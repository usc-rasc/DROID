#include <iostream>
#include <set>
#include <queue>
#include <ontology/node.h>
#include <ontology/ontology.h>
#include <ontology/searchtree.h>

int main()
{
    Ontology ontology( std::cin );
    ontology.printOntology();
    
    std::queue<int> mod;
    
    // For quick testing, add some nodes to be examined
    //mod.push(1);
    //mod.push(0);
    //mod.push(14);
    //oComplete.listInterfaceAttributes(mod);
    std::cout << "==================================================" << std::endl;
    
    SearchTree search_tree( ontology );
    search_tree.selectInterfacesSample();
    
    return 0;
}
