/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sandwich.cpp
//
// Created By: Bryan J Muscedere
// Date: 7/21/2016
//
// Class that represents a sandwich. Holds the recipe being referenced by the
// sandwich as well as any substitutions that are being made. Calculates the
// total cost after the substitutions.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Sandwich.h"
#include <vector>

using namespace std;

/**
 * Constructor that creates a new sandwich from a recipe.
 * @param current The recipe to be based on.
 */
Sandwich::Sandwich(Recipe* current){
    //Creates a recipe with NO substitution.
    baseRecipe = current;
    subList = NULL;
}

/**
 * Constructor that creates a new sandwich from
 * a recipe and a substitution.
 * @param current The recipe to be based on.
 * @param subs The substitution to be based on.
 */
Sandwich::Sandwich(Recipe* current, Substitution* subs){
    //Creates a recipe with substitution.
    baseRecipe = current;
    subList = subs;
}

/**
 * Deletes the sandwich and substitution.
 */
Sandwich::~Sandwich(){
    //Check if we have a null subList.
    if (subList != NULL)
        delete subList;
    subList = NULL;
}

/**
 * Checks if we can make the sandwich based
 * on the ingredient availability.
 * @return Boolean indicating whether we can make.
 */
bool Sandwich::canMake(){
    //We iterate through the ingredients.
    bool canMake;
    if (subList != NULL){
        canMake = baseRecipe->canMake(subList->getRemovals());
    } else {
        canMake = baseRecipe->canMake();
    }
    if (!canMake) return false;

    //Check additions.
    if (subList != NULL){
        vector<Ingredient*> additions = subList->getAdditions();
        for (int i = 0; i < additions.size(); i++){
            if (additions.at(i)->canUse() == false) return false;
        }
    }

    return true;
}

/**
 * Makes the sandwich by using ingredients in the sandwich
 * bar.
 * @return Whether the sandwich was made.
 */
bool Sandwich::make(){
    //Check if we can make it.
    if (!canMake()) return false;

    //Now, we make the base recipe.
    if (subList != NULL){
        baseRecipe->make(subList->getRemovals());
    } else {
        baseRecipe->make();
    }

    //Apply the additions.
    if (subList != NULL){
        vector<Ingredient*> additions = subList->getAdditions();
        for (int i = 0; i < additions.size(); i++){
            additions.at(i)->useIngredient();
        }
    }

    return true;
}

/**
 * Gets the total cost of the sandwich based on the
 * recipe and substitution.
 * @return The total cost of the sandwich.
 */
float Sandwich::getTotalCost(){
    float totalCost = baseRecipe->getTotalCost();
    if (subList != NULL) {
        totalCost += subList->getTotalAddCost();
        totalCost -= subList->getTotalRemoveCost();
    }

    return totalCost;
}

/**
 * Gets the referenced recipe of the sandwich.
 * @return The recipe.
 */
Recipe Sandwich::getRecipe(){
    return *baseRecipe;
}

/**
 * Checks whether we have a substitution.
 * @return Boolean indicating whether the sandwich has a substitution.
 */
bool Sandwich::hasSubstitution(){
    if (subList == NULL){
        return false;
    }

    return true;
}

/**
 * Gets the substitution or creates an empty one.
 * @return The substitution of the sandwich.
 */
Substitution Sandwich::getSubstitution(){
    if (subList == NULL){
        return Substitution();
    }

    return *subList;
}

/**
 * Prints details about the sandwich.
 * Refers to other print methods.
 * @return String with sandwich details.
 */
string Sandwich::print(){
    //Generates the sandwich string first.
    string sand = "A " + baseRecipe->getName() + " sandwich";

    //Lists the substitution.
    if (subList != NULL){
        sand += " with " + subList->printSubstitution();
    } else {
        sand += ".";
    }

    return sand;
}