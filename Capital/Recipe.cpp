/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Recipe.cpp
//
// Created By: Bryan J Muscedere
// Date: 7/21/2016
//
// Dictates how a standard recipe operates. Has functions to allow for
// making the recipe and checking the ingredients involved.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iomanip>
#include <sstream>
#include "Recipe.h"
#include "../SandwichBar.h"

using namespace std;

/**
 * Constructor for the recipe class. Creates
 * based on ingredients, the preimum and name.
 * @param name The name of the recipe.
 * @param ings The ingredients for the recipe.
 * @param premium The premium that he recipe uses.
 */
Recipe::Recipe(std::string name, std::vector<Ingredient*> ings, float premium){
    //Sets the name and list of ingredients.
    this->name = name;
    listOfIngredients = ings;
    this->premium = premium;

    //Used for testing Grok functionality.
    SandwichBar::numItems++;

    //Manages the references.
    manageReferences();
}

/**
 * Default destructor. Nothing to delete.
 */
Recipe::~Recipe(){ }

/**
 * Gets the total cost of the recipe.
 * Includes the premium.
 * @return The total recipe cost.
 */
float Recipe::getTotalCost(){
    return subComponentCost() + premium;
}

/**
 * Gets the cost of the recipe.
 * Only ingredient cost.
 * @return The raw cost of the recipe.
 */
float Recipe::getRawCost(){
    return subComponentCost();
}

/**
 * Indicates whether the recipe can be made.
 * @return A boolean indicating whether the recipe can be made.
 */
bool Recipe::canMake(){
    return canMakeIngredients();
}

/**
 * Makes the recipe by using the inventory.
 * @return Whether the recipe was made.
 */
bool Recipe::make(){
    return makeIngredients();
}

/**
 * Indicates whether the recipe can be made.
 * Ignores removed ingredients.
 * @param removed A vector of ingredients to be removed.
 * @return Boolean indicating whether it can be made.
 */
bool Recipe::canMake(std::vector<Ingredient*> removed){
    return canMakeIngredients(removed);
}

/**
 * Makes the recipe.
 * Ignores removed ingredients.
 * @param removed A vector of removed ingredients.
 * @return Boolean indicating success of it being made.
 */
bool Recipe::make(std::vector<Ingredient*> removed){
    return makeIngredients(removed);
}

/**
 * Creates a string of name and status.
 * @return A string with the name and status.
 */
string Recipe::print(){
    return printNameStatus();
}

/**
 * Creates a string with details of the recipe.
 * Includes more information than just name and status.
 * @return A string with recipe details.
 */
string Recipe::printDetails(){
    //Prints a more detailed look.
    string text = printNameStatus();

    //Prints the use.
    text += "\t- Uses: {";
    for (int i = 0; i < listOfIngredients.size(); i++){
        text += listOfIngredients.at(i)->getName();
        if (i + 1 < listOfIngredients.size()){
            text += ", ";
        }
    }
    text += "}\n";

    //Prints the used by.
    text += "\t- Referenced By: " + printReferences();
    text += "\n";

    return text;
}

/**
 * Gets the recipe name.
 * @return String with the name.
 */
string Recipe::getName(){
    return name;
}

/**
 * Gets all ingredients in the recipe.
 * @return A vector of ingredients in the recipe.
 */
vector<Ingredient*> Recipe::getIngredients(){
    return listOfIngredients;
}

/**
 * Checks whether a recipe contains an ingredient.
 * Searches through the recipe list.
 * @param ingName The name of the ingredient.
 * @return A boolean indicating whether the ingredient exists.
 */
bool Recipe::containsIngredient(string ingName){
    return findIngredient(ingName);
}

void Recipe::updateReferences(std::vector<Food*> references){
    //We first go an update ourselves.
    addReferences(references);

    //We now add ourselves.
    references.push_back(this);

    //We finally go through the ingredients.
    for (int i = 0; i < listOfIngredients.size(); i++){
        listOfIngredients.at(i)->updateReferences(references);
    }
}

/**
 * Helper method that looks for an ingredient by name.
 * @param ingName The name of the ingredient.
 * @return Boolean indicating whether it exists.
 */
bool Recipe::findIngredient(string ingName){
    //Iterate through to find it.
    for (int i = 0; i < listOfIngredients.size(); i++){
        if (ingName.compare(listOfIngredients.at(i)->getName()) == 0){
            return true;
        }
    }

    return false;
}

/**
 * Helper method that returns the ingredients involved.
 * @return A vector of the ingredients.
 */
vector<Ingredient*> Recipe::getSubComponents(){
    return listOfIngredients;
}

/**
 * Computes the cost of the ingredients at
 * this level of the recipe.
 * @return The cost of the ingredients.
 */
float Recipe::subComponentCost() {
    float cost = 0;

    for (int i = 0; i < listOfIngredients.size(); i++)
        cost += listOfIngredients.at(i)->getCost();

    return cost;
}

/**
 * Helper method which checks whether recipe can be made.
 * @return Whether the recipe can be made.
 */
bool Recipe::canMakeIngredients(){
    //Iterate through the list of ingredients to check.
    for (int i = 0; i < listOfIngredients.size(); i++){
        if (listOfIngredients.at(i)->canUse() == false){
            return false;
        }
    }

    return true;
}

/**
 * Makes the ingredients listed at this level of the
 * recipe.
 * @return Boolean indicating success.
 */
bool Recipe::makeIngredients(){
    if (!canMakeIngredients()) return false;

    //Iterate and use.
    for (int i = 0; i < listOfIngredients.size(); i++){
        listOfIngredients.at(i)->useIngredient();
    }

    return true;
}

/**
 * Helper method which checks whether the ingredients
 * can be made at this level. Ignores removed ingredients.
 * @param removed A vector of removed ingredients.
 * @return Boolean indicating success.
 */
bool Recipe::canMakeIngredients(vector<Ingredient*> removed){
    //We iterate through each of the ingredients.
    for (int i = 0; i < listOfIngredients.size(); i++){
        Ingredient* current = listOfIngredients.at(i);
        bool removedIng = false;

        //Iterate through the removed list.
        for (int j = 0; j < removed.size(); j++){
            if (current == removed.at(j)){
                removedIng = true;
                break;
            }
        }

        if (!removedIng && !current->canUse()){
            return false;
        }
    }

    return true;
}

/**
 * Helper method which makes ingredients at this level
 * of the recipe. Ignores removed ingredients.
 * @param removed Vector of removed ingredients.
 * @return A boolean indicating success.
 */
bool Recipe::makeIngredients(vector<Ingredient*> removed){
    //Check if we can use it.
    if (!canMakeIngredients(removed)) return false;

    //We iterate through each of the ingredients.
    for (int i = 0; i < listOfIngredients.size(); i++){
        Ingredient* current = listOfIngredients.at(i);
        bool removedIng = false;

        //Iterate through the removed list.
        for (int j = 0; j < removed.size(); j++){
            if (current == removed.at(j)){
                removedIng = true;
                break;
            }
        }

        if (!removedIng){
            current->useIngredient();
        }
    }

    return true;
}

/**
 * Prints the name and status of the recipe.
 * @return String with name and status.
 */
string Recipe::printNameStatus(){
    string text = name + ":\n\t- ";

    //Formats the cost and total cost.
    stringstream costStream;
    costStream << fixed
               << setprecision(2)
               << setfill( '0' ) << getTotalCost();
    text += "Total Cost: $" + costStream.str();

    //Clears and reobtains.
    costStream.str("");
    costStream << fixed
               << setprecision(2)
               << setfill( '0' ) << getRawCost();
    text += "\n\t- Raw Ingredient Cost: $" + costStream.str();
    costStream.clear();

    text += "\n\t- ";

    if (canMake())
        text += "Can Make";
    else
        text += "Cannot Make";
    text += "\n";

    return text;
}