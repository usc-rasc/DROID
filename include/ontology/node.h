#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>

#include <ontology/olink.h>

/*********************
 * This class represents a node in the ontology.  It will be one modality,
 * requirement, resource, etc...  The nodes will be connected via olinks to
 * create a network.
 */

class Node
{
private:
    int _id;
    std::string _name;
    std::vector<Olink> _links;
    std::vector<Olink> _back_links;

public:
    Node();
    Node( std::string const & name, int const & id );
    // Get the ID of the node
    int const & getID() const;

    // Print the contents of this node
    void printNode() const;

    // Set the ID of the node
    void setID( int const & id );

    // Set the name of the node
    void setName( std::string const & name );

    // Add a link to the node.
    void addLink( std::string const & name, int const & end_node );

    void addLink( Olink const & link );

    // Add a backlink to this node (a link *in* from another node
    void addBackLink( Olink const & link );

    // Iterate over the links and change the start node to be the current node.
    void fixLinks();

    // Get the links out from this node
    std::vector<Olink> const & getLinks() const;

    // Get the links out from this node which have a name found in "Relationships"
    std::vector<Olink> getLinks( std::set<std::string> const & relationships ) const;

    // Get the requirements of this node
    std::set<int> getRequirements() const;

    // Get the resources this node provides
    std::set<int> getResourcesProvided() const;

    // Get the list of nodes which provide this resource
    std::set<int> getSuppliers() const;

    // Get the list attributes associated with this node
    std::map<int, int> getAttributes() const;

    // Get the list of BackLInks into this node, ie.  links from other nodes into this one
    std::vector<Olink> const & getBackLinks() const;

    std::vector<Olink> getBackLinks( std::set<std::string> relationships ) const;

    // Get the name of this node
    std::string const & getName() const;
};

#endif
