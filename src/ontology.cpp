#include <ontology/ontology.h>

Ontology::Ontology()
{
    //
}

/********************************************************************************
* Constructor function.  Reads the nodes and links from a file
* specified by 'filename'.
********************************************************************************/
Ontology::Ontology( std::string const & filename )
{
    std::cerr << "Reading Ontology from file:" << filename << std::endl;

    std::ifstream ontology_file( filename );

    if( ontology_file.is_open() )
    {
        parseOntology( ontology_file );
        ontology_file.close();
    }
    else
    {
        std::cerr << "unable to open file: " << filename << std::endl;
    }
}

Ontology::Ontology( std::istream & input_stream )
{
    parseOntology( input_stream );
}

/********************************************************************************
* Constructor function.  Reads the nodes and links from a file
* specified by 'filename'.
********************************************************************************/
void Ontology::parseOntology( std::istream & input_stream )
{
    std::string line;
    std::string token;

    // Get the line from the file
    while( std::getline( input_stream, line ) )
    {
        // each line is a node
        Node node;
        // std::cerr << line  << std::endl;
        std::istringstream ss( line );

        // We have the line in 'line'.  Time to parse.
        // First split on the semicolons.  ';'
        while( std::getline( ss, token, ';' ) )
        {
            // Each token is potentially a new link (anything except 'name' and 'id'

            // Create the link
            Olink link;

            // Now need to split 'token' on ':'
            // token should be 'relationship:target'
            std::string relationship;
            std::string target;
            std::istringstream ss2( token );
            std::getline( ss2, relationship, ':' );
            std::getline( ss2, target );

            // If the relationship is 'name' then set the node name
            if( relationship.compare( "name" ) == 0 )
            {
                node.setName( target );
                // If the relationship is 'id' then set the node name
            }
            else if( relationship.compare( "id" ) == 0 )
            {
                node.setID( std::atoi( target.c_str() ) );
            }
            else
            {
                // Need to check if the liink has a parameter
                // Check the "relationship" variable to see if something is in () A
                // First, see if anything exists before a opening paren
                size_t opening_p = relationship.find( "(" ); // )

                if( opening_p != std::string::npos ) // )
                {
                    std::cerr << "Parameter found!!!!!" << opening_p << " " << opening_p + 1 << std::endl;
                    // (
                    size_t closing_p = relationship.find( ")" ); //
                    std::cerr << "Closing found at " << closing_p << std::endl;
                    std::string val = relationship.substr( opening_p + 1, closing_p - opening_p - 1 );
                    std::string name = relationship.substr( 0, opening_p );
                    std::cerr << "Parameter value: " << name << " " << val << std::endl;
                    // Update the link info
                    link.setInfo2( name, std::atoi( target.c_str() ) );
                    link.setValue( atoi( val.c_str() ) );
                    // Add the link to the node
                    node.addLink( link );
                }
                else
                {
                    // Otherwise, just update as usual
                    // Update the link info
                    link.setInfo2( relationship, std::atoi( target.c_str() ) );
                    // Add the link to the node
                    node.addLink( link );
                }
            }
        } // while (std::getline(ss, token, ';'))

        // Add the node to the ontology
        node.fixLinks();
        addNode( node );
    }

    // Now need to iterate over the ontology and add the backlinks
    // Iterate over all the nodes
    if( _nodes.size() == 0 )
    {
        std::cerr << "There are no nodes in the ontology." << std::endl;
    }
    else
    {
        for( int node_idx = 0; node_idx < _nodes.size(); ++node_idx )
        {
            Node const & node = _nodes[node_idx];

            // for each node, get the set of links
            std::vector<Olink> const & links = node.getLinks();

            // For each link, look at the start_id, and end_id.  Reverse them, make a link, and add it to the
            // backlink of the end_id node
            for( int link_idx = 0; link_idx < links.size(); ++link_idx )
            {
                Olink const & link = links[link_idx];

                int const start_id = link.getStart();
                int const end_id = link.getEnd();

                Olink const back_link( link.getName(), end_id, start_id );
                _nodes[end_id].addBackLink( back_link );
            }
        }
    }
}

/********************************************************************************
* Traverse through the now-read in ontology to add all the backlinks to the nodes
********************************************************************************/
void Ontology::addBackLinks() const
{
    //
}

/********************************************************************************
* Add a node to the ontology with name n_name and id n_id.  This function *might*
* have been made obsolete after recent changes.
********************************************************************************/
void Ontology::addNode( std::string const & name, int const & id )
{
    // if this node is larger than the current vector length,
    // then resize the vector to accomodate
    if( _nodes.capacity() <= id )
    {
        _nodes.resize( id + 1 );
    }

    _nodes[id] = Node( name, id );
}

/********************************************************************************
* Add a new node to the ontology.  This node has already been created and only
* needs to be inserted
********************************************************************************/
void Ontology::addNode( Node const & new_node )
{
    int id = new_node.getID();

    // if this node is larger than the current vector length,
    // then resize the vector to accomodate
    if( _nodes.size() <= id + 1 )
    {
        _nodes.resize( id + 1 );
    }

    // Nodes.push_back(new_node);
    _nodes[id] = new_node;

    // Check this node.  If it is 'requirements', 'operator', 'robot', or 'enviornment'
    // we need to store that info

    if( new_node.getName().compare( "requirements" ) == 0 )
    {
        std::cerr << "Found the requirements node" << std::endl;
        _requirements_node_id = new_node.getID();
    }

    if( new_node.getName().compare( "operator" ) == 0 )
    {
        std::cerr << "Found the operator node" << std::endl;
        _operator_node_id = new_node.getID();
    }

    if( new_node.getName().compare( "robot" ) == 0 )
    {
        std::cerr << "Found the robot node" << std::endl;
        _robot_node_id = new_node.getID();
    }

    if( new_node.getName().compare( "environment" ) == 0 )
    {
        std::cerr << "Found the environment node" << std::endl;
        _environment_node_id = new_node.getID();
    }
}

/********************************************************************************
* Print out the Ontology
********************************************************************************/

void Ontology::printOntology() const
{
    std::cerr << "=============================================" << std::endl;
    std::cerr << "Print Ontology..." << std::endl;
    std::cerr << "Number of nodes: " << _nodes.size() << std::endl;
    std::cerr << "Requirements Node ID: " << _requirements_node_id << std::endl;
    std::cerr << "Operator Node ID: " << _operator_node_id << std::endl;
    std::cerr << "Robot Node ID: " << _robot_node_id << std::endl;
    std::cerr << "Environment Node ID: " << _environment_node_id << std::endl;

    if( _nodes.size() == 0 )
    {
        std::cerr << "There are no nodes in the ontology." << std::endl;
    }
    else
    {
        for( int node_idx = 0; node_idx < _nodes.size(); ++node_idx )
        {
            _nodes[node_idx].printNode();
        }
    }

    std::cerr << "=============================================" << std::endl;
}

/********************************************************************************
* Print out dot file.  Visualize using vimdot
********************************************************************************/

void Ontology::printDotFile( std::string const & filename ) const
{
    std::ofstream dotfile( filename );

    if( dotfile.is_open() )
    {
        printDotFile( dotfile );
        dotfile.close();
    }
    else
    {
        std::cerr << "unable to write file: " << filename << std::endl;
    }
}

void Ontology::printDotFile( std::ostream & output_stream ) const
{
    // Iterate over all the nodes in the ontology.
    if( _nodes.empty() )
    {
        std::cerr << "There are no nodes in the ontology." << std::endl;
    }
    else
    {
        output_stream << "digraph Ontology {" << std::endl;

        // first print the main nodes;
        output_stream << "\t\toperator [ color=\"red\"];" << std::endl;
        output_stream << "\t\trobot [ color=\"blue\"];" << std::endl;
        output_stream << "\t\trequirements [ color=\"green\"];" << std::endl;
        output_stream << "\t\tenvironment [ color=\"orange\"];" << std::endl;

        for( int node_idx = 0; node_idx < _nodes.size(); ++node_idx )
        {
            Node const & node = _nodes[node_idx];

            std::vector<Olink> const & links( node.getLinks() );

            for( int link_idx  = 0; link_idx < links.size(); ++link_idx )
            {
                Olink const & link = links[link_idx];

                // For each link, get the start and end
                Node const & start_node = _nodes[link.getStart()];
                Node const & end_node = _nodes[link.getEnd()];

                std::string label = link.getName();

                output_stream << "\t\t" << start_node.getName() << " -> " << end_node.getName();

                if( link.isValued() )
                {
                    output_stream << " [ label =\"" << label << "(" << link.getValue() << ")\"];" << std::endl;
                }
                else
                {
                    output_stream << " [ label =\"" << label << "\"];" << std::endl;
                }
            }
        }
        // For each node, iterate over each link and add that to the graph

        output_stream << "}0" << std::endl;
    }
}

/********************************************************************************
* Search through the ontology starting at 'start_id' and list out the attributes
********************************************************************************/
void Ontology::listInterfaceAttributes( std::queue<int> modalities ) const
{
    int start_id;

    std::set<std::string> relationships;
    relationships.insert( "represents" );
    relationships.insert( "displays" );

    std::cerr << "Analyzing ontology" << std::endl;
    // iterate over the list of modalities
    // using only start_id for now, but this should become a vector or array

    while( !modalities.empty() )
    {
        start_id = modalities.front();
        modalities.pop();

        Node const & start_node = _nodes[start_id];
        std::vector<Olink> const & links = start_node.getLinks();
        std::cerr << "\t" << start_node.getName() << std::endl;

        // Iterate over the set of links
        for( int link_idx = 0; link_idx < links.size(); ++link_idx )
        {
            Olink const & link = links[link_idx];

            std::cerr << "\t\t" << link.getName() << " : ";

            Node const & end_node = _nodes[link.getEnd()];

            std::cerr << end_node.getName() << std::endl;

            // Need to follow specific link names
            if( relationships.find( link.getName() ) != relationships.end() )
            {
                modalities.push( end_node.getID() );
            }
        }
    }
}

/********************************************************************************
* Check if a node is equipment on the robot (or potentially on the robot)
********************************************************************************/
bool Ontology::isRobotEquipment( Node const & node ) const
{
    // check if one of the Backlinks into the node is an 'is' from 'robot
    // if so, return True, otherwise, return False
    std::set<std::string> relationships;
    relationships.insert( "has" );

    std::vector<Olink> back_links = node.getBackLinks( relationships );

    if( back_links.empty() )
    {
        return false;
    }

    for( int link_idx = 0; link_idx < back_links.size(); ++link_idx )
    {
        Olink const & link = back_links[link_idx];

        Node const & original_node = _nodes[link.getEnd()];

        if( original_node.getName().compare( "robot" ) == 0 )
        {
            return true;
        }
    }

    return false;
}

/********************************************************************************
* Return the node with nodeID
********************************************************************************/
Node const & Ontology::getNode( int const & node_id ) const
{
    return _nodes[node_id];
}

/********************************************************************************
* Get the requirements node ID
********************************************************************************/
int const & Ontology::getRequirementsNodeID() const
{
    return _requirements_node_id;
}

/********************************************************************************
* Get the requirements node ID
********************************************************************************/
Node const & Ontology::getRequirementsNode() const
{
    std::cerr << "ontology.cpp: Returning requirements node" << std::endl;
    return getNode( getRequirementsNodeID() );
}
