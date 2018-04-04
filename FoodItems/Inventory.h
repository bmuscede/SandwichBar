/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inventory.h
//
// Created By: Bryan J Muscedere
// Date: 7/21/2016
//
// System that manages all the ingredients stored at the
// sandwich bar. Allows users to add, remove and use ingredients
// stored here.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SANDWICH_BAR_INVENTORY_H
#define SANDWICH_BAR_INVENTORY_H

#include <string>
#include <vector>
#include "Ingredient.h"

class Inventory {

public:
    /** Constructor/Destructor */
    Inventory();
    ~Inventory();

    /** Add Methods */
    bool addSimpleIngredient(std::string name, int quantity, float cost);
    bool addComplexIngredient(std::string name,
                              float premium, std::vector<Ingredient*>* basedOn);

    /** Remove Methods */
    void removeIngredient(Ingredient* ing);
    bool removeIngredient(std::string ingName);

    /** Inventory Methods */
    bool exists(std::string name);
    Ingredient* getIngredient(std::string name);
    std::string getInventoryDetails();
    int getInventorySize();

    /** Simulation Methods */
    Ingredient* getRandomIngredient();

private:
    /** Private Variables */
    std::vector<Ingredient*>* pantry;

    /** Helper Methods */
    int findItem(std::string name);
};


#endif //SANDWICH_BAR_INVENTORY_H
