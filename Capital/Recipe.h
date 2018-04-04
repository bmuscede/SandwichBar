/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Recipe.h
//
// Created By: Bryan J Muscedere
// Date: 7/21/2016
//
// Dictates how a standard recipe operates. Has functions to allow for
// making the recipe and checking the ingredients involved.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SANDWICH_BAR_RECIPE_H
#define SANDWICH_BAR_RECIPE_H

#include <string>
#include <vector>
#include "../FoodItems/Food.h"
#include "../FoodItems/Ingredient.h"

class Recipe : public Food {
public:
    /** Constructor/Destructor */
    Recipe(std::string name, std::vector<Ingredient*> ings, float premium);
    virtual ~Recipe();

    /** Cost Methods */
    virtual float getTotalCost();
    virtual float getRawCost();

    /** Make Methods */
    virtual bool canMake();
    virtual bool make();
    virtual bool canMake(std::vector<Ingredient*> removed);
    virtual bool make(std::vector<Ingredient*> removed);

    /** Print Methods */
    virtual std::string print();
    virtual std::string printDetails();
    std::string getName();

    /** Ingredient Methods */
    virtual std::vector<Ingredient*> getIngredients();
    virtual bool containsIngredient(std::string ingName);

    /** Update Method */
    virtual void updateReferences(std::vector<Food*> references);

protected:
    /** Protected Variables */
    float premium;

    /** Helper Methods */
    bool findIngredient(std::string ingName);
    std::vector<Ingredient*> getSubComponents();
    float subComponentCost();
    bool canMakeIngredients();
    bool makeIngredients();
    bool canMakeIngredients(std::vector<Ingredient*> removed);
    bool makeIngredients(std::vector<Ingredient*> removed);
    std::string printNameStatus();

private:
    /** Private Variable */
    std::string name;
    std::vector<Ingredient*> listOfIngredients;
};


#endif //SANDWICH_BAR_RECIPE_H
