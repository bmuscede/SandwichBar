/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inventory.cpp
//
// Created By: Bryan J Muscedere
// Date: 7/21/2016
//
// System that manages all the ingredients stored at the
// sandwich bar. Allows users to add, remove and use ingredients
// stored here.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Inventory.h"
#include "SimpleIngredient.h"
#include "ComplexIngredient.h"

using namespace std;

/**
 * Constructor which creates an
 * empty pantry.
 */
Inventory::Inventory(){
    //Create the pantry.
    pantry = new vector<Ingredient*>();
}

/**
 * Destructor which deletes all items in the
 * pantry then deletes the pantry.
 */
Inventory::~Inventory(){
    //First, delete all pantry items.
    for (int i = 0; i < pantry->size(); i++)
        delete pantry->at(i);

    delete pantry;
}

/**
 * Adds a new simple ingredient to the pantry.
 * @param name The name of the ingredient.
 * @param quantity The quantity of the ingredient.
 * @param cost The cost of the ingredient.
 * @return Boolean indicating success.
 */
bool Inventory::addSimpleIngredient(string name, int quantity, float cost){
    Ingredient* simple = new SimpleIngredient(name, quantity, cost);
    pantry->push_back(simple);

    return true;
}

/**
 * Adds a new complex ingredient to the pantry.
 * @param name The name of the ingredient.
 * @param premium The premium of the ingredient.
 * @param basedOn What the ingredient is based on.
 * @return Boolean indicating success.
 */
bool Inventory::addComplexIngredient(string name,
                                     float premium, vector<Ingredient*>* basedOn){
    Ingredient* complex = new ComplexIngredient(name, premium, basedOn);
    pantry->push_back(complex);

    return true;
}

/**
 * Removes an ingredient from the pantry based on pointer.
 * @param ing A pointer to the ingredient.
 */
void Inventory::removeIngredient(Ingredient* ing){
    delete ing;

    //Removes the element from the vector.
    for (int i = 0; i < pantry->size(); i++){
        if (pantry->at(i) == NULL){
            pantry->erase(pantry->begin() + i);
            break;
        }
    }
}

/**
 * Removes an ingredient from the pantry based on name.
 * @param ingName The name of the ingredient.
 * @return Boolean indicating success.
 */
bool Inventory::removeIngredient(string ingName){
    int index = findItem(ingName);
    pantry->erase(pantry->begin() + index);

    return true;
}

/**
 * Checks whether an ingredient exists by name.
 * @param name The name of the ingredient.
 * @return A boolean indicating whether it exists.
 */
bool Inventory::exists(string name){
    int index = findItem(name);

    //Check to see if the item exists.
    if (index == -1) return false;
    return true;
}

/**
 * Gets an ingredient by name.
 * @param name The name of the ingredient.
 * @return A pointer to the ingredient in the pantry.
 */
Ingredient* Inventory::getIngredient(string name){
    Ingredient* current = NULL;
    int index = findItem(name);
    if (index != -1) current = pantry->at(index);

    return current;
}

/**
 * Prints information about the inventory.
 * @return String with inventory information.
 */
string Inventory::getInventoryDetails(){
    string items = "INVENTORY DETAILS\n";
    items += "----------------------------------\n";

    if (pantry->size() == 0) {
        items += "No items in inventory.";
        return items;
    }

    //Iterates to generate text.
    for (int i = 0; i < pantry->size(); i++)
        items += pantry->at(i)->getName()
                 + ": x" + to_string(pantry->at(i)->getQuantity()) + "\n";

    return items;
}

/**
 * Gets the size of the pantry.
 * @return The inventory size.
 */
int Inventory::getInventorySize(){
    return pantry->size();
}

/**
 * Gets a random ingredient from the pantry.
 * @return A pointer to the random ingredient.
 */
Ingredient* Inventory::getRandomIngredient(){
    //Seeds random.
    srand(time(NULL));
    return pantry->at(rand() % pantry->size());
}

/**
 * Finds an ingredient by name stored in the inventory.
 * @param name The name of the ingredient.
 * @return The position of the ingredient in the vector.
 */
int Inventory::findItem(std::string name){
    int index = -1;
    string current;

    //Iterate through vector to find.
    for (int i = 0; i < pantry->size(); i++){
        current = pantry->at(i)->getName();
        if (current.compare(name) == 0) {
            index = i;
            break;
        }
    }

    return index;
}