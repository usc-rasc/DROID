#include <ontology/node.h>

/********************************************************************************
* Get the ID of the node
********************************************************************************/
int const & Node::getID() const
{
    return _id;
}

/********************************************************************************
* Default Node Constructor
********************************************************************************/
Node::Node()
{
    //
}

/********************************************************************************
*  // Node constructor given the name and id of the node
********************************************************************************/
Node::Node( std::string const & name, int const & id )
:
    _name( name ),
    _id( id )
{
    //
}

/********************************************************************************
*  // Print the information in the node
********************************************************************************/
void Node::printNode() const
{
    std::cerr << "ID: " << _id << " Name: " << _name << std::endl;
    std::cerr << "\tLinks:" << std::endl;

    for( int i = 0; i < _links.size(); i++ )
    {
        _links[i].printLink();
    }

    std::cerr << "\tBackLinks:" << std::endl;

    for( int i = 0; i < _back_links.size(); i++ )
    {
        _back_links[i].printLink();
    }
}

/********************************************************************************
*  // Set the ID number of the node
********************************************************************************/
void Node::setID( int const & id )
{
    _id = id;
}

/********************************************************************************
* Set the name of the node
********************************************************************************/
void Node::setName( std::string const & name )
{
    _name = name;
}

/********************************************************************************
* Add a link to the node.
********************************************************************************/
void Node::addLink( Olink const & link )
{
    _links.push_back( link );
}

/********************************************************************************
* Add a back link to the node.
********************************************************************************/
void Node::addBackLink( Olink const & link )
{
    _back_links.push_back( link );
}

/********************************************************************************
* Iterate over the links and change the start node to be the current node.
********************************************************************************/
void Node::fixLinks()
{
    for( int i = 0; i < _links.size(); i++ )
    {
        _links[i].setStart( _id );
    }
}

/********************************************************************************
* Return a list of the links in a node
********************************************************************************/
std::vector<Olink> const & Node::getLinks() const
{
    return _links;
}

/********************************************************************************
* Return a list of the links to the node
* ONLY return the links with names in 'relationships'
********************************************************************************/
std::vector<Olink> Node::getLinks( std::set<std::string> const & relationships ) const
{
    std::vector<Olink> link_subset;

    // Iterate over the Backlinks
    for( int i = 0; i < _links.size(); i++ )
    {
        if( relationships.find( _links[i].getName() ) != relationships.end() )
        {
            // Add that node to the subset
            link_subset.push_back( _links[i] );
        }
    }

    return link_subset;
}

/********************************************************************************
* Return a list of REQUIREMENTS of the node
********************************************************************************/
std::set<int> Node::getRequirements() const
{
    std::set<std::string> requirements_names;
    requirements_names.insert( "requires" );

    std::set<int> requirements;

    std::vector<Olink> const & requirements_list = getLinks( requirements_names );
    // construct the in version of this

    for( int requirement_idx = 0; requirement_idx < requirements_list.size(); ++requirement_idx )
    {
        requirements.insert( requirements_list[requirement_idx].getEnd() );
    }

    return requirements;
}

/********************************************************************************
* Return a list of reources provided by the node
********************************************************************************/
std::set<int> Node::getResourcesProvided() const
{
    std::set<std::string> requirements_names;
    requirements_names.insert( "provides" );
    requirements_names.insert( "has" );

    std::set<int> requirements;

    std::vector<Olink> const & requirements_list = getLinks( requirements_names );
    // construct the in version of this

    for( int requirement_idx = 0; requirement_idx < requirements_list.size(); ++requirement_idx )
    {
        requirements.insert( requirements_list[requirement_idx].getEnd() );
    }

    return requirements;
}

/********************************************************************************
* Return a list of nodes which provide this resource
********************************************************************************/

std::set<int> Node::getSuppliers() const
{
    std::set<std::string> supply_link_name;
    supply_link_name.insert( "provides" );
    supply_link_name.insert( "has" );

    std::set<int> suppliers;

    std::vector<Olink> const & suppliers_list = getBackLinks( supply_link_name );
    // construct the in version of this

    for( int supplier_idx = 0; supplier_idx < suppliers_list.size(); ++supplier_idx )
    {
        suppliers.insert( suppliers_list[supplier_idx].getEnd() );
    }

    return suppliers;
}

// Get the list attributes associated with this node
std::map<int, int> Node::getAttributes() const
{
    std::set<std::string> attribute_link_name;
    attribute_link_name.insert( "attribute" );
    std::map<int, int> attribute_set;

    // Iterate over the links
    for( int link_idx = 0; link_idx < _links.size(); ++link_idx )
    {
        Olink const & link = _links[link_idx];

        // if the link is labelled "attribute", then we want to keep it
        if( attribute_link_name.find( link.getName() ) != attribute_link_name.end() )
        {
            std::cerr << "node.cpp : attribute found" << std::endl;
            // check if that node is valued
            int node_id = link.getEnd();

            if( link.isValued() )
            {
                attribute_set[node_id] = link.getValue();
            }
            else
            {
                attribute_set[node_id] = -1;
            }
        }
    }

    return attribute_set;
}

/********************************************************************************
* Return a list of the back links to the node
********************************************************************************/
std::vector<Olink> const & Node::getBackLinks() const
{
    return _back_links;
}

/********************************************************************************
* Return a list of the back links to the node
* ONLY return the links with names in 'relationships'
********************************************************************************/
std::vector<Olink> Node::getBackLinks( std::set<std::string> relationships ) const
{
    std::vector<Olink> back_link_subset;

    // Iterate over the Backlinks
    for( int i = 0; i < _back_links.size(); i++ )
    {
        if( relationships.find( _back_links[i].getName() ) != relationships.end() )
        {
            // Add that node to the subset
            back_link_subset.push_back( _back_links[i] );
        }
    }

    return back_link_subset;
}

/********************************************************************************
* Return a list of the links in a node
********************************************************************************/
std::string const & Node::getName() const
{
    return _name;
}
