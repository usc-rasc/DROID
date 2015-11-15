#ifndef ONTOLOGY_H
#define ONTOLOGY_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <cstdlib>
#include <set>
#include <queue>
#include <time.h>

#include <ontology/node.h>

/*! The ontology is a network of nodes connected by links that captures the
 * information about all the potential modalities, resources, and information
 * available.  The ontology contains all possible available information, which
 * is then searched to find a subset (or interface) which meets the
 * requirements.
 */

class Ontology
{
protected:
    // / The list of nodes in the ontology
    std::vector<Node> _nodes;
    // / The total number of nodes
    int _num_nodes;
    // / ID of the requirements node
    int _requirements_node_id;
    // / ID of the operator node
    int _operator_node_id;
    // / ID of the robot node
    int _robot_node_id;
    // / ID of the environment node
    int _environment_node_id;

    // /  Add the back links from a node, going back from the child to the parents
    void addBackLinks() const;

public:
    static std::string const & getFileExtension()
    {
        static const std::string file_extension( "ont" );
        return file_extension;
    }

    // / Default constructor function
    Ontology();

    // / Constructor function.  Reads ontology from a file

    /*!
     * @param filename the name of the file to be loaded
     */
    Ontology( std::string const & filename );

    Ontology( std::istream & input_stream );

    void parseOntology( std::istream & input_stream );

    // / Print out everything in the ontology
    void printOntology() const;

    // / Add a node to the ontology with name and id.  Creates the node from the information

    /*!
     * \param n_name the name of the node to add
     * \param n_id the id of the node to add
     */
    void addNode( std::string const & name, int const & id );

    // / Add a node to the ontology.

    /*!
     * \param new_node the node to be added
     */
    void addNode( Node const & new_node );

    // / print the ontology as a dot graphic file format

    /*!
     * \param filename The name of dot file to output
     */
    void printDotFile( std::string const & filename ) const;

    void printDotFile( std::ostream & output_stream ) const;

    // / Search through the ontology starting at 'start_id' and list out the attributes

    /*!
     * \param modalities The list of modalities in the currently selected interface
     */
    void listInterfaceAttributes( std::queue<int> modalities ) const;

    // / Is this current node a piece of robot equipment.  Originally for older algorithm which was removed
    bool isRobotEquipment( Node const & node ) const;

    // / Return the node in the ontology with id == nodeID
    Node const & getNode( int const & node_id ) const;

    // / Get the ID of the requirements node
    int const & getRequirementsNodeID() const;

    // /  Get the requirements node
    Node const & getRequirementsNode() const;

    // Make the children of a current interface
    // vector <ModInterface> makeChildren(ModInterface I);
};

#endif
