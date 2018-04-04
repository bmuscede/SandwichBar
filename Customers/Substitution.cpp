/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Substitution.cpp
//
// Created By: Bryan J Muscedere
// Date: 7/21/2016
//
// Represents substitutions that are being made to a sandwich in
// an order. Contains a list of substituted ingredients.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Substitution.h"

using namespace std;

/**
 * Creates a new substitution with
 * empty vectors.
 */
Substitution::Substitution(){
    //Creates empty vectors to hold ingredients.
    additions = vector<Ingredient*>();
    removals = vector<Ingredient*>();
}

/**
 * Creates a substitution with specified
 * additions and removals.
 * @param add A vector of additions.
 * @param remove A vector of removals.
 */
Substitution::Substitution(std::vector<Ingredient*> add, std::vector<Ingredient*> remove){
    //Creates vectors to hold the substitution values.
    additions = add;
    removals = remove;
}

/**
 * Default destructor.
 */
Substitution::~Substitution(){ }

/**
 * Adds a new addition.
 * @param add The ingredient to add.
 */
void Substitution::addAddition(Ingredient* add){
    additions.push_back(add);
}

/**
 * Adds a new removal.
 * @param remove The ingredient to remove.
 */
void Substitution::addRemoval(Ingredient* remove){
    removals.push_back(remove);
}

/**
 * Gets the total cost of all additions.
 * @return The cost of all ingredient additions.
 */
float Substitution::getTotalAddCost(){
    return calculateCost(additions);
}

/**
 * Gets the total cost of all removals.
 * @return The cost of all ingredients to remove.
 */
float Substitution::getTotalRemoveCost(){
    return calculateCost(removals);
}

/**
 * Prints the details of the substitution.
 * @return String of substitutions.
 */
string Substitution::printSubstitution(){
    string results = "a substitution of";

    //Prints additions.
    if (additions.size() != 0) results += " added ";
    for (int i = 0; i < additions.size(); i++){
        results += additions.at(i)->getName();

        if (i + 1 != additions.size()){
            results += ", ";
        }
        if (i + 2 == additions.size()){
            results += "and ";
        }
    }

    //Prints removals.
    if (removals.size() != 0) {
        if (additions.size() != 0) results += " and";
        results += " no ";
    }
    for (int i = 0; i < removals.size(); i++){
        results += removals.at(i)->getName();

        if (i + 1 != removals.size()){
            results += ", ";
        }
        if (i + 2 == removals.size()){
            results += "or ";
        }
    }

    results += ".";
    return results;
}

/**
 * Gets the additions.
 * @return A vector of additions.
 */
std::vector<Ingredient*> Substitution::getAdditions(){
    return additions;
}

/**
 * Gets the removals
 * @return A vector of removals.
 */
std::vector<Ingredient*> Substitution::getRemovals(){
    return removals;
}

/**
 * Calculates the total cost of a list of ingredients.
 * @param list The list of ingredients to calculate.
 * @return The total cost.
 */
float Substitution::calculateCost(vector<Ingredient*> list){
    float total = 0;
    for (int i = 0; i < list.size(); i++){
        total += list.at(i)->getCost();
    }

    return total;
}