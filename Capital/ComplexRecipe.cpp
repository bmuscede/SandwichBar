/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ComplexRecipe.cpp
//
// Created By: Bryan J Muscedere
// Date: 7/26/2016
//
// Dictates how a complex recipe operates. Has functions to allow for
// making the recipe and checking the ingredients involved. Based
// on the basic recipe but extended to build upon other recipes.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ComplexRecipe.h"

using namespace std;

/**
 * Constructor for the complex recipe. Takes a lot of parameters
 * to set up this instance.
 * @param name The name of the recipe.
 * @param ings The ingredients to add.
 * @param base The base recipe.
 * @param removed The ingredients to remove.
 * @param premium The recipe premium.
 */
ComplexRecipe::ComplexRecipe(string name, vector<Ingredient*> ings,
        Recipe* base, vector<Ingredient*> removed, float premium) : Recipe(name, ings, premium){
    //Sets the base recipe and the removed items.
    baseRecipe = base;
    removedIngredients = removed;

    //Manages the references.
    manageReferences();
}

/**
 * Default destructor. Nothing to delete.
 */
ComplexRecipe::~ComplexRecipe(){ }

/**
 * Gets the total cost of the recipe.
 * Includes the premium.
 * @return The total recipe cost.
 */
float ComplexRecipe::getTotalCost(){
    return getRawCost() + premium;
}

/**
 * Gets the cost of the recipe.
 * Only ingredient cost.
 * @return The raw cost of the recipe.
 */
float ComplexRecipe::getRawCost(){
    float cost = 0;

    //First, get the base cost.
    cost += baseRecipe->getTotalCost();
    cost += subComponentCost();
    for (int i = 0; i < removedIngredients.size(); i++)
        cost -= removedIngredients.at(i)->getCost();

    return cost;
}

/**
 * Indicates whether the recipe can be made.
 * @return A boolean indicating whether the recipe can be made.
 */
bool ComplexRecipe::canMake(){
    //Check if we can make the base recipe.
    if (!baseRecipe->canMake(removedIngredients)) return false;

    //Next, we check if we can make the added ingredients.
    return canMakeIngredients();
}

/**
 * Makes the recipe by using the inventory.
 * @return Whether the recipe was made.
 */
bool ComplexRecipe::make(){
    //Check if we can make it.
    if (!canMake()) return false;

    //Now, we make the recipe.
    baseRecipe->make(removedIngredients);
    makeIngredients();

    return true;
}

/**
 * Indicates whether the recipe can be made.
 * Ignores removed ingredients.
 * @param removed A vector of ingredients to be removed.
 * @return Boolean indicating whether it can be made.
 */
bool ComplexRecipe::canMake(std::vector<Ingredient*> removed){
    //Merge the removed with removals.
    vector<Ingredient*> removeList = mergeRemovals(removed);

    //Check if we can make.
    if (!baseRecipe->canMake(removeList)) return false;

    //Next, we check if we can make the added ingredients.
    return canMakeIngredients(removed);
}

/**
 * Makes the recipe.
 * Ignores removed ingredients.
 * @param removed A vector of removed ingredients.
 * @return Boolean indicating success of it being made.
 */
bool ComplexRecipe::make(std::vector<Ingredient*> removed){
    //Check if we can make it.
    if (!canMake(removed)) return false;

    //Merge the removed with removals.
    vector<Ingredient*> removeList = mergeRemovals(removed);

    //Now, we make the recipe.
    baseRecipe->make(removeList);
    makeIngredients(removed);

    return true;
}

/**
 * Creates a string of name and status.
 * @return A string with the name and status.
 */
string ComplexRecipe::print(){
    string text = printNameStatus();
    text += "\t- Based On: " + baseRecipe->getName() + "\n";

    return text;
}

/**
 * Creates a string with details of the recipe.
 * Includes more information than just name and status.
 * @return A string with recipe details.
 */
string ComplexRecipe::printDetails(){
    //Prints a more detailed look.
    string text = printNameStatus();

    //Prints the use.
    text += "\t- Uses: {";

    //Gets the ingredients.
    vector<Ingredient*> ings = getIngredients();
    for (int i = 0; i < ings.size(); i++){
        text += ings.at(i)->getName();
        if (i + 1 < ings.size()){
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
 * Gets all ingredients in the recipe.
 * @return A vector of ingredients in the recipe.
 */
vector<Ingredient*> ComplexRecipe::getIngredients() {
    //Creates an updated list of ingredients.
    vector<Ingredient*> concatList = vector<Ingredient*>();
    vector<Ingredient*> baseIngredients = baseRecipe->getIngredients();
    vector<Ingredient*> addedIngredients = getSubComponents();

    //Now, merges all the lists together.
    concatList.insert(concatList.end(), baseIngredients.begin(), baseIngredients.end());
    for (int i = 0; i < addedIngredients.size(); i++){
        bool exists = false;

        for (int j = 0; j < concatList.size(); j++){
            if (addedIngredients.at(i) == concatList.at(j)) exists = true;
        }

        if (!exists) concatList.push_back(addedIngredients.at(i));
    }
    for (int i = 0; i < removedIngredients.size(); i++){
        for (int j = 0; j < concatList.size(); j++){
            if (removedIngredients.at(i) == concatList.at(j)) {
                concatList.erase(concatList.begin() + j);
                break;
            }
        }
    }

    return concatList;
}

/**
 * Checks whether a recipe contains an ingredient.
 * Searches through the recipe list.
 * @param ingName The name of the ingredient.
 * @return A boolean indicating whether the ingredient exists.
 */
bool ComplexRecipe::containsIngredient(string ingName){
    //Check if the base recipe has it but also checks if its in the removal.
    if (findIngredient(ingName) && !findRemoval(ingName)){
        return true;
    }

    return false;
}

void ComplexRecipe::updateReferences(std::vector<Food*> references){
    //We first pass the references to ourselves.
    addReferences(references);

    //We now add ourselves.
    references.push_back(this);

    //We now call the base recipe.
    baseRecipe->updateReferences(references);

    //Finally, we call our ingredients.
    vector<Ingredient*> listOfIngredients = getSubComponents();
    for (int i = 0; i < listOfIngredients.size(); i++){
        listOfIngredients.at(i)->updateReferences(references);
    }
}

/**
 * Checks whether an item has been removed.
 * Goes through the removal list based on a name.
 * @param ingName The name of the ingredient to find.
 * @return Boolean indicating whether it has been found.
 */
bool ComplexRecipe::findRemoval(string ingName){
    //Check if the removal exists.
    for (int i = 0; i < removedIngredients.size(); i++){
        if (removedIngredients.at(i)->getName().compare(ingName) == 0){
            return true;
        }
    }

    return false;
}

/**
 * Takes two vectors and merges them into one.
 * Does this to amalgamate removal lists.
 * @param removeOne Vector of removed items.
 * @return Combined vector.
 */
vector<Ingredient*> ComplexRecipe::mergeRemovals(vector<Ingredient*> removeOne){
    vector<Ingredient*> removeList = vector<Ingredient*>();
    removeList.insert(removeList.end(), removeOne.begin(), removeOne.end());
    removeList.insert(removeList.end(), removedIngredients.begin(), removedIngredients.end());

    return removeList;
}