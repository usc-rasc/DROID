#ifndef SEARCHTREE_H
#define SEARCHTREE_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <stack>

#include <ontology/modinterface.h>
#include <ontology/ontology.h>

/* Need to search over possible interfaces to find one which meets the
 * requirements of the ontology.  This search tree allows for searching in
 * traditional DFS, BFS, and potentially A* search approaches.  Each node in
 * the treee is a complete interface.  New nodes are constructed by taking
 * existing interfaces and adding new modalities, untill all requirements are
 * met. */

class SearchTree
{
protected:
    std::queue<ModInterface> _search_queue;
    Ontology _ontology;
    // list of nodes which have already been examined.
    std::set<ModInterface> _examined_nodes;

public:
    // The constructor function.  Takes in an already-loaded ontology
    SearchTree();
    SearchTree( Ontology database );
    // Constructor function. Takes in a file name to load
    // SearchTree(std::string const & filename);

    // Search to find a potential interface which meets the requirements using
    // the ontology as the database.
    // XXX Returning void for now, change to ModInterface later
    void selectInterfacesSample();

    void addNode( ModInterface new_node );

    void addNode( std::vector<ModInterface> node_list );  // add a bunch of new nodes to the tree

    ModInterface returnNext();  // return the next node to be searched in the tree

    bool isEmpty(); // returns true if the tree is empty.
};

#endif
