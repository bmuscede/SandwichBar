/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ComplexRecipe.h
//
// Created By: Bryan J Muscedere
// Date: 7/26/2016
//
// Dictates how a complex recipe operates. Has functions to allow for
// making the recipe and checking the ingredients involved. Based
// on the basic recipe but extended to build upon other recipes.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SANDWICH_BAR_COMPLEXRECIPE_H
#define SANDWICH_BAR_COMPLEXRECIPE_H

#include "Recipe.h"

class ComplexRecipe : public Recipe {
public:
    /** Constructors/Destructors */
    ComplexRecipe(std::string name, std::vector<Ingredient*> ings,
            Recipe* base, std::vector<Ingredient*> removed, float premium);
    ~ComplexRecipe();

    /** Cost Methods */
    float getTotalCost();
    float getRawCost();

    /** Make Methods */
    bool canMake();
    bool make();
    bool canMake(std::vector<Ingredient*> removed);
    bool make(std::vector<Ingredient*> removed);

    /** Print Methods */
    std::string print();
    std::string printDetails();

    /** Ingredient Methods */
    std::vector<Ingredient*> getIngredients();
    bool containsIngredient(std::string ingName);

    /** Update Method */
    void updateReferences(std::vector<Food*> references);
private:
    /** Private Variables */
    Recipe* baseRecipe;
    std::vector<Ingredient*> removedIngredients;

    /** Helper Methods */
    bool findRemoval(std::string ingName);
    std::vector<Ingredient*> mergeRemovals(std::vector<Ingredient*> removeOne);
};


#endif //SANDWICH_BAR_COMPLEXRECIPE_H
