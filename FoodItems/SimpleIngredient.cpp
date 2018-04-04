/////////////////////////////////////////////////////////////////////////////////////////////////////////
// SimpleIngredient.cpp
//
// Created By: Bryan J Muscedere
// Date: 7/22/2016
//
// Dictates how a simple ingredient operates. Allows users to use the
// ingredient. Order more instances of it, and print its details.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SimpleIngredient.h"

using namespace std;

/**
 * Creates a simple ingredient instance based on several
 * parameters including the name, cost, and number of instances.
 * @param name The name of the ingredient.
 * @param quantity The number of instances.
 * @param cost The cost of the recipe.
 */
SimpleIngredient::SimpleIngredient(string name, int quantity, float cost)
    : Ingredient(name) {
    this->quantity = quantity;
    this->cost = cost;

    //Manages the references.
    manageReferences();
}

/**
 * Destructor
 */
SimpleIngredient::~SimpleIngredient(){ }

/**
 * Orders more of this ingredient.
 * @param amount The amount to order.
 */
void SimpleIngredient::orderMore(int amount){
    quantity += amount;
}

/**
 * Gets the cost of the ingredient.
 * @return The cost of the ingredient.
 */
float SimpleIngredient::getCost(){
    return cost;
}

/**
 * Gets the quantity of the ingredient.
 * @return The quantity of the ingredient.
 */
int SimpleIngredient::getQuantity(){
    return quantity;
}

/**
 * Checks whether we have enough of this ingredient.
 * @return Boolean indicating whether we can use it.
 */
bool SimpleIngredient::canUse() {
    if (quantity == 0) return false;
    return true;
}

/**
 * Uses the ingredient by decrimenting the number of instances.
 * @return Boolean indicating whether it was used.
 */
bool SimpleIngredient::useIngredient() {
    //Check if we can use that ingredient.
    if (quantity == 0) {
        return false;
    }

    //Decrement the quantity otherwise.
    quantity--;
    return true;
}

/**
 * Prints details associated with the ingredient.
 * @return A string with ingredient details.
 */
string SimpleIngredient::printDetails() {
    string text = printHeader();
    text += "\t- Referenced By: " + printReferences();
    text += "\n";

    return text;
}

void SimpleIngredient::updateReferences(std::vector<Food*> references){
    //We simply pass these references to the update function.
    addReferences(references);
}