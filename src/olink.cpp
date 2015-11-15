#include <ontology/olink.h>

/********************************************************************************
* Print out the link information
********************************************************************************/
void Olink::printLink() const
{
    if( _is_valued )
    {
        std::cerr << "\t\tLink Name: " << _name << " Nodes (" << _start_node << "," << _end_node << ") V: " << _value << std::endl;
    }
    else
    {
        std::cerr << "\t\tLink Name: " << _name << " Nodes (" << _start_node << "," << _end_node << ")" << std::endl;
    }
}

/********************************************************************************
* Constructor function with no info
********************************************************************************/
Olink::Olink()
{
    _is_valued = false;
}

/********************************************************************************
* Constructor function with all info
********************************************************************************/
Olink::Olink( std::string const & name, int const & node1, int const & node2 )
{
    _name = name;
    _start_node = node1;
    _end_node = node2;
    _is_valued = false;
}

/********************************************************************************
* Set the name of the link
********************************************************************************/
void Olink::setName( std::string const & name )
{
    _name = name;
}

/********************************************************************************
* Set the starting node of the link
********************************************************************************/
void Olink::setStart( int const & node_id )
{
    _start_node = node_id;
}

/********************************************************************************
* Set the ending node of the link
********************************************************************************/
void Olink::setEnd( int const & node_id )
{
    _end_node = node_id;
}

/********************************************************************************
* Set all the information of the node
********************************************************************************/
void Olink::setInfo( std::string const & name, int const & node1, int const & node2 )
{
    _name = name;
    _start_node = node1;
    _end_node = node2;
}

/********************************************************************************
* Set all the information of the node
********************************************************************************/
void Olink::setInfo2( std::string const & name, int const & node2 )
{
    _name = name;
    _end_node = node2;
}

/********************************************************************************
* Set the value of the node, and set the valued parameter to be true
********************************************************************************/
void Olink::setValue( int const & value )
{
    _value = value;
    _is_valued = true;
}

/********************************************************************************
* Return the id of the start node of the link
********************************************************************************/
int const & Olink::getStart() const
{
    return _start_node;
}

/********************************************************************************
* Return the id of the end node of the link
********************************************************************************/
int const & Olink::getEnd() const
{
    return _end_node;
}

/********************************************************************************
* Return the name of the link
********************************************************************************/
std::string const & Olink::getName() const
{
    return _name;
}

/********************************************************************************
* Does the link have a value associated with it?
********************************************************************************/
bool const & Olink::isValued() const
{
    return _is_valued;
}

/********************************************************************************
* Return the value of the link
********************************************************************************/
int const & Olink::getValue() const
{
    return _value;
}
