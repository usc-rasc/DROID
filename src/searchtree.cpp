#include <ontology/searchtree.h>

/************************************************************
* Constructor.  Uses an existing ontology
************************************************************/
SearchTree::SearchTree()
{
    //
}

/************************************************************
* Constructor.  Uses an existing ontology
************************************************************/
SearchTree::SearchTree( Ontology database )
{
    std::cerr << "searchtree.cpp: Creating Search Tree.  Using a queue representation (BFS)." << std::endl;
    std::cerr << "searchtree.cpp: Copying ontology" << std::endl;
    _ontology = database;
}

/************************************************************
* Add a node to the tree.  Will need to check if it is a repeat or not.  Add
* to either the stack, queue, or priority queue based on sorting method.
************************************************************/
void SearchTree::addNode( ModInterface new_node )
{
    // need to check for loops.  ie. maintain a set of visited nodes.
    // Check if the new node has already been examined

    std::set<ModInterface>::iterator iter;

    for( iter = _examined_nodes.begin(); iter != _examined_nodes.end(); ++iter )
    {
        if( new_node.compare( *iter ) )
        {
            return;
        }
    }

    // if not, then add it to the queue.

    _search_queue.push( new_node );
}

/************************************************************
* Add a vector of nodes to the tree.
************************************************************/
void SearchTree::addNode( std::vector<ModInterface> node_list )
{
    // Iterate over node_list and call addNode for each
    for( int node_idx = 0; node_idx < node_list.size(); ++node_idx )
    {
        addNode( node_list[node_idx] );
    }
}

/*************************************************************
*
* return if the tree is empty or not
*
*************************************************************/
bool SearchTree::isEmpty()
{
    std::cerr << ( _search_queue.empty() ? "_search_queue is empty" : "_search_queue is not empty" ) << std::endl;

    return _search_queue.empty();
}

/************************************************************
* Return the next node in the tree.
************************************************************/
ModInterface SearchTree::returnNext()
{
    ModInterface new_interface = _search_queue.front();

    _search_queue.pop();

    return new_interface;
}

/************************************************************
*  Search to find a potential interface which meets the requirements using the
*  ontology as the database.
************************************************************/

void SearchTree::selectInterfacesSample()
{
    // Create list of requirements
    // Initalized from ontology
    // Create list of currently selected modalities
    // Create list of met requirements
    // for each item in requirements list
    // check if requirement has already been met
    // If not met yet
    // Follow the "provides" backlinks --> Provides a list of potential modalities
    // Select one modality from the list randomly
    // Version 1) Add Modality.  Add requirements of modality. Add requirements it provides
    // Assume requirement is met, add it to list of completed requirements
    // Repeat until requirements list empty
    // Need to check if all requirements can be met.  If not, then start over.
    // Version 2) Iterate on modality.  Make sure requirements can be met before adding

    // Add the initial set of requirements by adding the requirements node
    ModInterface current_interface;

    std::vector<ModInterface> candidate_interfaces;

    current_interface.addModality( _ontology.getRequirementsNode() );
    current_interface.print();

    // push the initial modality onto the search "tree" (ie. queue)
    addNode( current_interface );

    // Now repeat until
    // 1) we have an interface with remaining requirements
    // or 2) until search tree is empty.  If empty, then fail.

    // while ((!isEmpty()) && current_interface.hasRequirements())
    while( !isEmpty() )
    {
        std::cerr << "******************************************" << std::endl;
        std::cerr << "Examining node" << std::endl;
        current_interface.print();

        // Be careful about data structures here, we have Nodes, Interfaces, and a SearchTree

        if( !current_interface.hasRequirements() )
        {
            // add it to the list
            candidate_interfaces.push_back( current_interface );
        }
        else
        {
            // 1) Generate the children of the current interface
            // vector <ModInterface> children = _ontology.makeChildren(current_interface);
            std::vector<ModInterface> children = current_interface.makeChildren( _ontology );

            // 2) Add those children to the tree
            addNode( children );

            // 3) Get the next interface to examine from the tree
        }

        current_interface = returnNext();
    }

    std::cerr << "\n\n********************************************************************************" << std::endl;
    std::cerr << "********************************************************************************" << std::endl;

    for( int i = 0; i < candidate_interfaces.size(); i++ )
    {
        candidate_interfaces[i].print( _ontology );
        std::cerr << "********************************************************************************" << std::endl;
    }
}
