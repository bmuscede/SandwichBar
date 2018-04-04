/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Substitution.h
//
// Created By: Bryan J Muscedere
// Date: 7/21/2016
//
// Represents substitutions that are being made to a sandwich in
// an order. Contains a list of substituted ingredients.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SANDWICH_BAR_SUBSTITUTION_H
#define SANDWICH_BAR_SUBSTITUTION_H

#include <string>
#include <vector>
#include "../FoodItems/Ingredient.h"

class Substitution {
public:
    /** Constructor/Destructor */
    Substitution();
    Substitution(std::vector<Ingredient*> add, std::vector<Ingredient*> remove);
    ~Substitution();

    /** Add Operations */
    void addAddition(Ingredient* add);
    void addRemoval(Ingredient* remove);

    /** Cost Operations */
    float getTotalAddCost();
    float getTotalRemoveCost();

    /** Print Operations */
    std::string printSubstitution();

    /** Get Operations */
    std::vector<Ingredient*> getAdditions();
    std::vector<Ingredient*> getRemovals();

private:
    /** Private Variables */
    std::vector<Ingredient*> additions;
    std::vector<Ingredient*> removals;

    /** Helper Methods */
    float calculateCost(std::vector<Ingredient*> list);
};


#endif //SANDWICH_BAR_SUBSTITUTION_H
