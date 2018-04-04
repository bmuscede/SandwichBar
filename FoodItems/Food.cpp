/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Food.cpp
//
// Created By: Bryan J Muscedere
// Date: 7/22/2016
//
// Master class for the recipes and ingredients in the system. Can't be
// initialized directly but keeps track of how all the items reference
// each other.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Food.h"
#include "../SandwichBar.h"

using namespace std;

/**
 * Empty destructor.
 */
Food::~Food(){ }

/**
 * Constructor which creates a blank referenced
 * by list.
 */
Food::Food(){
    referencedBy = vector<Food*>();
}

void Food::manageReferences(){
    updateReferences(vector<Food*>());
}

/**
 * Gets all items that reference this food item.
 * @return A vector with all food refererences.
 */
vector<Food*> Food::getReferences(){
    return referencedBy;
}

/**
 * Prints the references that are referencing
 * this food item.
 * @return String containing the references.
 */
string Food::printReferences(){
    if (referencedBy.size() == 0) return "None";
    string text = "{";

    //Print the references
    for (int i = 0; i < referencedBy.size(); i++){
        text += referencedBy.at(i)->getName();
        if (i + 1 < referencedBy.size()){
            text += ", ";
        }
    }
    text += "}";

    return text;
}

void Food::addReferences(std::vector<Food*> references){
    //Check if we have duplicates.
    for (int i = 0; i < references.size(); i++){
        bool dup = false;

        for (int j = 0; j < referencedBy.size(); j++){
            if (referencedBy.at(j) == references.at(i)) {
                dup = true;
                break;
            }
        }

        //Adds in the current entry if no duplicates.
        if (dup == false) referencedBy.push_back(references.at(i));
    }
}
