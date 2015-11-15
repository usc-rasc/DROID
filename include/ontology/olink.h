#ifndef OLINK_H
#define OLINK_H

#include <iostream>
#include <string>

/* Olinks connect the nodes in the ontology.  These describe the relationships
 * between the start node and end node.
 */

class Olink
{
private:
    int _start_node;
    int _end_node;
    std::string _name;
    int _value;
    bool _is_valued;

public:
    Olink();
    Olink( std::string const & name, int const & node1, int const & node2 );

    // Print the information about this link
    void printLink() const;

    // Set the name of this link
    void setName( std::string const & name );

    // Set the starting node of this link
    void setStart( int const & node_id );

    // Set the terminating node of this link
    void setEnd( int const & node_id );

    // Set all the info about this link at once
    void setInfo( std::string const & name, int const & node1, int const & node2 );

    void setInfo2( std::string const & name, int const & node2 );

    void setValue( int const & value );

    // Return the starting point of this link
    int const & getStart() const;

    // Return the end point of this link
    int const & getEnd() const;

    // Return the name of this link
    std::string const & getName() const;

    // is the link a valued link? (has a numeric value associated with it)
    bool const & isValued() const;

    int const & getValue() const;  // return that value
};

#endif
