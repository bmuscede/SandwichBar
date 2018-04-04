/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sandwich.h
//
// Created By: Bryan J Muscedere
// Date: 7/21/2016
//
// Class that represents a sandwich. Holds the recipe being referenced by the
// sandwich as well as any substitutions that are being made. Calculates the
// total cost after the substitutions.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SANDWICH_BAR_SANDWICH_H
#define SANDWICH_BAR_SANDWICH_H

#include "../Capital/Recipe.h"
#include "Substitution.h"

class Sandwich {
public:
    /** Constructor/Destructor */
    Sandwich(Recipe* current);
    Sandwich(Recipe* current, Substitution* subs);
    ~Sandwich();

    /** Make Operations */
    bool canMake();
    bool make();

    /** Sandwich Operations */
    float getTotalCost();
    Recipe getRecipe();
    bool hasSubstitution();
    Substitution getSubstitution();

    /** Print Methods */
    std::string print();

private:
    /** Private Variables */
    Recipe* baseRecipe;
    Substitution* subList;
    float totalCost;
};


#endif //SANDWICH_BAR_SANDWICH_H
