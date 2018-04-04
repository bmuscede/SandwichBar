/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ComplexIngredient.cpp
//
// Created By: Bryan J Muscedere
// Date: 7/22/2016
//
// Dictates how a complex ingredient operates. Allows users to use the
// ingredient. Order more instances of it, and print its details. Also
// relies on the simple ingredient to operate.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include "ComplexIngredient.h"

using namespace std;

/**
 * Creates a complex ingredient instance based on several
 * parameters including the name, premium and based on details.
 * @param name The name of the ingredient.
 * @param premium The ingredient premium.
 * @param basedOn A vector indicating the ingredient base.
 */
ComplexIngredient::ComplexIngredient(string name, float premium, vector<Ingredient*>* basedOn) : Ingredient(name) {
    //First, set the premium price.
    this->premium = premium;
    this->basedOn = basedOn;

    //Manages the references.
    manageReferences();
}

/**
 * Destructor which deletes the based on vector.
 */
ComplexIngredient::~ComplexIngredient() {
    //Delete the based on vector.
    delete basedOn;
}

/**
 * Orders more of this ingredient.
 * Orders more sub-ingredients too.
 * @param amount The amount to order.
 */
void ComplexIngredient::orderMore(int amount) {
    Ingredient* lowest = NULL;

    //First, get the lowest quantity.
    Ingredient* current;
    for (int i = 0; i < basedOn->size(); i++){
        current = basedOn->at(i);

        //Check if we have nothing.
        if (lowest == NULL){
            lowest = current;
        } else if (lowest->getQuantity() > current->getQuantity()){
            lowest = current;
        }
    }

    //Get lowest amount.
    int lowAmount = lowest->getQuantity();

    //Iterate through all and update.
    for (int i = 0; i < basedOn->size(); i++){
        basedOn->at(i)->orderMore(amount -
                                 (basedOn->at(i)->getQuantity() - lowAmount));
    }
}

/**
 * Gets the cost of the ingredient based on
 * the premium and sub-ingredient costs.
 * @return The cost of the ingredient.
 */
float ComplexIngredient::getCost(){
    float cost = premium;

    //Iterate through all other ingredients and get their cost.
    for (int i = 0; i < basedOn->size(); i++){
        cost += basedOn->at(i)->getCost();
    }

    return cost;
}

/**
 * Gets the number of instances of this ingredient.
 * @return The number of instances.
 */
int ComplexIngredient::getQuantity() {
    int lowestItem = INT_MAX;

    //Loops through all base items.
    for (int i = 0; i < basedOn->size(); i++){
        int currentItem = basedOn->at(i)->getQuantity();

        if (currentItem < lowestItem)
            lowestItem = currentItem;
    }

    return lowestItem;
}

/**
 * Checks whether we have enough of this ingredient.
 * @return Boolean indicating whether we can use it.
 */
bool ComplexIngredient::canUse(){
    for (int i = 0; i < basedOn->size(); i++){
        if (basedOn->at(i)->getQuantity() <= 0) {
            return false;
        }
    }

    return true;
}

/**
 * Uses the ingredient by decrimenting the number of instances.
 * @return Boolean indicating whether it was used.
 */
bool ComplexIngredient::useIngredient(){
    //First, we need to perform a sanity check.
    bool valid = true;
    for (int i = 0; i < basedOn->size(); i++){
        if (basedOn->at(i)->canUse() == false){
            return false;
        }
    }

    //Otherwise, decrement all quantities.
    for (int i = 0; i < basedOn->size(); i++){
        basedOn->at(i)->useIngredient();
    }

    return true;
}

/**
 * Prints details associated with the ingredient.
 * @return A string with ingredient details.
 */
string ComplexIngredient::printDetails() {
    string text = printHeader();

    //Next, we print the base ingredients.
    text += "\t- Uses: {";
    for (int i = 0; i < basedOn->size(); i++){
        text += basedOn->at(i)->getName();

        if (i + 1 < basedOn->size()){
            text += ", ";
        }
    }
    text += "}\n";

    //Now, print the references.
    text += "\t- Referenced By: " + printReferences();
    text += "\n";

    return text;
}

void ComplexIngredient::updateReferences(std::vector<Food*> references){
    //First, passes the references to the update function.
    addReferences(references);

    //Add ourselves to the current reference list.
    references.push_back(this);

    //Now, we go through the references and update them.
    for (int i = 0; i < basedOn->size(); i++){
        basedOn->at(i)->updateReferences(references);
    }
}