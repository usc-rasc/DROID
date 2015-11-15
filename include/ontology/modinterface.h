#ifndef MODINTERFACE_H
#define MODINTERFACE_H

#include <iostream>
#include <algorithm>
#include <map>

#include <ontology/node.h>
#include <ontology/ontology.h>

/* The interface object will include information about the current interface,
 * including the current modalities selected, the current requirements met, and
 * the remaining requirements to be met. */

class ModInterface
{
protected:
    std::set<int> _current_modalities;    // Modalities in the current interface
    std::set<int> _requirements_met;   // The requirements met by the current interface
    std::set<int> _requirements_left;   // the requirements required by the current interface which have not currently been met

    std::map<int, int> _attributes;

public:
    ModInterface();

    // Add a modality to the current interface.
    void addModality( Node modality );

    // Get the requirements of the current interface
    std::set<int> getRequirements();

    // Check if the current interface has any requirements
    bool hasRequirements();

    // Print otu the current interface
    void print();

    void print( Ontology ontology );

    // Print otu the current interface
    bool compare( ModInterface const & mod_interface );

    bool operator==( ModInterface & mod_interface )
    {
        return compare( mod_interface );
    }

    std::vector<ModInterface> makeChildren( Ontology ontology );
};

#endif
