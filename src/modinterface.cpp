#include <ontology/modinterface.h>

ModInterface::ModInterface()
{
    //
}

/************************************************************
 * Add a modality to the interface
 *************************************************************/
void ModInterface::addModality( Node modality )
{
    std::cerr << "modinterface.cpp:\tAdding modality: " << modality.getName() << std::endl;

    // Add the modality
    _current_modalities.insert( modality.getID() );

    // Add it's requirements
    std::set<int> requirements = modality.getRequirements();
    std::vector<int> temp_required;

    std::set<int> new_requirements;

    // Creating NewRequirementsAll   ***********************
    // Need to make the union between the old requirements set on the new requirements added
    // Update the _requirements_left
    if( _requirements_left.empty() )
    {
        new_requirements = requirements;
    }
    else if( requirements.empty() )
    {
        // no change to Requirements
        new_requirements = _requirements_left;
    }
    else
    {
        // set_union(requirements.begin(), requirements.end(),
        // _requirements_left.begin(), _requirements_left.end(), temp_required.begin());
        std::set_union( requirements.begin(), requirements.end(), _requirements_left.begin(), _requirements_left.end(), inserter( temp_required, temp_required.end() ) );
        new_requirements = std::set<int>( temp_required.begin(), temp_required.end() );
    }

    // Creating _requirements_met   ***********************
    // new_requirements now has ALL the old requirements plus the new
    // requirements added by the new modality.  This may include requirements
    // already met, as well as the requirements for which this modality was
    // added.

    // Next we add the requirements met by the new modality to the old set of requirements met.
    // This gives us ALL the requirements met by the new interface.

    std::vector<int> temp_provided;
    std::set<int> provided = modality.getResourcesProvided();

    if( _requirements_met.empty() )
    {
        // if the current requirements list is empty, just make it the requirements
        // provided by the modality we just added.
        _requirements_met = provided;
    }
    else
    {
        // otherwise, combine it with the previous _requirements_met list

        /*  set_union(provided.begin(), provided.end(),
         *    _requirements_met.begin(), _requirements_met.end(), temp_provided.begin());*/
        std::set_union( provided.begin(), provided.end(), _requirements_met.begin(), _requirements_met.end(), inserter( temp_provided, temp_provided.end() ) );
        std::set<int> new_requirements_met( temp_provided.begin(), temp_provided.end() );
        _requirements_met = new_requirements_met;
    }

    // Creating _requirements_left   ***********************
    // We have now updated all the requirements met by the current interface,
    // including the most recently added modality.   We need to filter out stuff
    // from the requirements.  We'll find the elements in new_requirements but
    // NOT in _requirements_met.  This will then become _requirements_left.
    std::vector<int> requirements_remaining;

    // if new_requirements is empty, it means there are currently no unmet requirements
    // if _requirements_met is empty, it means the current interface provides no resources
    if( new_requirements.empty() )
    {
        _requirements_left = new_requirements;
    }
    else if( _requirements_met.empty() )
    {
        _requirements_left = new_requirements;
    }
    else
    {
        std::set_difference( new_requirements.begin(), new_requirements.end(), _requirements_met.begin(), _requirements_met.end(), inserter( requirements_remaining, requirements_remaining.end() ) );
        _requirements_left = std::set<int>( requirements_remaining.begin(), requirements_remaining.end() );
    }

    // Time to add the _attributes.
    // Need to account for valued links as well.
    // This will be tricky.  If the attribute is valued, and already is listed, then increment by the value.
    // Otherwise, initialize

    // We'll be using a map for this.  Hash table style.
    // key on the attribute ID.

    // 1) Get the list of _attributes of the current modality

    std::map<int, int> attr = modality.getAttributes();

    // Iterate over the _attributes.

    if( attr.empty() )
    {
        std::cerr << "modinterface.cpp: Node has no _attributes" << std::endl;
    }
    else
    {
        std::cerr << "modinterface.cpp: Attributes not empty" << std::endl;

        for( std::map<int, int>::iterator it = attr.begin(); it != attr.end(); ++it )
        {
            int a = it->first;
            int v = it->second;
            // 2) Check of that attribute has already been added to the list

            std::cerr << "Attributes: " << it->first << " " << it->second << std::endl;

            if( _attributes.find( it->first ) == _attributes.end() )
            {
                std::cerr << "modinterface.cpp: Attribute already exists in interface. " << std::endl;

                // if it's not valued, then don't worry.  Already there.
                if( v >= 0 )
                {
                    _attributes[a] = _attributes[a] + v;
                }

                // not found
            }
            else
            {
                std::cerr << "modinterface.cpp: Attribute new to interface. " << std::endl;

                _attributes[a] = v;
            }

            // 3) If not, then
        }
    }

    // set <int> requirements_remainingTemp(requirements_remaining.begin(), requirements_remaining.end());
    // _requirements_left = requirements_remainingTemp;

    // Logic:  Add all of it's requirements to _requirements_left, then update
    // RequirementsMet, then remove _requirements_met from _requirements_left

    // Add the resources it provides

    // update the requirements based on the resources it provides

    // also update the _requirements_met;
}

/************************************************************
 * Return the list of unmet requirements of the interface.
 *************************************************************/

std::set<int> ModInterface::getRequirements()
{
    return _requirements_left;
}

/************************************************************
 * Does this interface still have requirements to fulfill?
 *************************************************************/

bool ModInterface::hasRequirements()
{
    if( _requirements_left.empty() )
    {
        return false;
    }
    else
    {
        return true;
    }
}

/************************************************************
 * Print out this interface
 *************************************************************/

void ModInterface::print()
{
    std::set<int>::iterator iter;

    std::cerr << "Modalities:" << std::endl;

    for( iter = _current_modalities.begin(); iter != _current_modalities.end(); ++iter )
    {
        std::cerr << "\t" << *iter << std::endl;
    }

    std::cerr << "_requirements_met:" << std::endl;

    for( iter = _requirements_met.begin(); iter != _requirements_met.end(); ++iter )
    {
        std::cerr << "\t" << *iter << std::endl;
    }

    std::cerr << "_requirements_left:" << std::endl;

    for( iter = _requirements_left.begin(); iter != _requirements_left.end(); ++iter )
    {
        std::cerr << "\t" << *iter << std::endl;
    }

    std::cerr << "_attributes:" << std::endl;

    std::map<int, int>::iterator it;

    for( std::map<int, int>::iterator it = _attributes.begin(); it != _attributes.end(); ++it )
    {
        // 2) Check of that attribute has already been added to the list

        // 3) If not, then

        std::cerr << "\t" << it->first << " " << it->second << std::endl;
    }
}

/************************************************************
 * Print out this interface.  Ontology input for better output
 *************************************************************/

void ModInterface::print( Ontology ontology )
{
    std::set<int>::iterator iter;

    std::cerr << "Modalities:" << std::endl;

    for( iter = _current_modalities.begin(); iter != _current_modalities.end(); ++iter )
    {
        std::cerr << "\t" << ontology.getNode( *iter ).getName() << " " << *iter << std::endl;
    }

    std::cerr << "_requirements_met:" << std::endl;

    for( iter = _requirements_met.begin(); iter != _requirements_met.end(); ++iter )
    {
        std::cerr << "\t" << ontology.getNode( *iter ).getName() << " " << *iter << std::endl;
    }

    std::cerr << "_requirements_left:" << std::endl;

    for( iter = _requirements_left.begin(); iter != _requirements_left.end(); ++iter )
    {
        std::cerr << "\t" << ontology.getNode( *iter ).getName() << " " << *iter << std::endl;
    }

    std::cerr << "_attributes:" << std::endl;

    std::map<int, int>::iterator it;

    for( std::map<int, int>::iterator it = _attributes.begin(); it != _attributes.end(); ++it )
    {
        // 2) Check of that attribute has already been added to the list

        // 3) If not, then
        std::cerr << "\tAttribute: " << ontology.getNode( it->first ).getName() << " value: " << it->second << std::endl;
    }
}

/************************************************************
 * Compare two interfaces
 *************************************************************/

bool ModInterface::compare( ModInterface const & mod_interface )
{
    if( _current_modalities != mod_interface._current_modalities ) return false;

    if( _requirements_met != mod_interface._requirements_met ) return false;

    if( _requirements_left != mod_interface._requirements_left ) return false;

    return true;
}

/********************************************************************************
 * Given an interface, make all the children of that interface
 *********************************************************************************/

std::vector<ModInterface> ModInterface::makeChildren( Ontology ontology )
{
    std::vector<ModInterface> children;
    // get all of it's requirements
    // _requirements_left = getRequirements();

    for( std::set<int>::iterator i = _requirements_left.begin(); i != _requirements_left.end(); i++ )
    {
        int current_requirement = *i;
        // For each requirement

        std::cerr << "\tChecking requirement " << current_requirement << std::endl;
        // Get the list of modalities which meet those requirements
        std::set<int> suppliers = ontology.getNode( current_requirement ).getSuppliers();
        std::cerr << "\t\tHas " << suppliers.size() << " suppliers" << std::endl;

        // For each of those modalities
        for( std::set<int>::iterator j = suppliers.begin(); j != suppliers.end(); j++ )
        {
            int current_modality = *j;

            std::cerr << "modinterface.cpp: Returning requirements node" << std::endl;
            // Create a new interface with that modality added
            ModInterface new_interface = *this;
            new_interface.addModality( ontology.getNode( current_modality ) );

            // is that modality new?  If so, cram it into the queue
            children.push_back( new_interface );
        }

        // otherwise, just ignore
    }

    return children;
}
