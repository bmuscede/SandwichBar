/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ingredient.cpp
//
// Created By: Bryan J Muscedere
// Date: 7/21/2016
//
// Shell class which contains common methods between the ComplexIngredient and
// SimpleIngredient. Joins the commonalities between these two classes. This
// class cannot be initialized by itself.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iomanip>
#include <sstream>
#include "Ingredient.h"
#include "../SandwichBar.h"

using namespace std;

/**
 * Destructor for the Ingredient class.
 */
Ingredient::~Ingredient() {};

/**
 * Gets the name of the ingredient.
 * @return The name of the ingredient.
 */
string Ingredient::getName(){
    return commonName;
}

/**
 * Constructor which sets the name of the ingredient.
 * @param name The name of the ingredient.
 */
Ingredient::Ingredient(string name) : commonName(name) {
    //Used for testing Grok functionality.
    SandwichBar::numItems++;
};

/**
 * Prints the name and cost of
 * the ingredient. This is the
 * same for both Simple and Complex.
 * @return String containing the header.
 */
string Ingredient::printHeader() {
    //Print the details.
    string text = getName() + ":\n\t- ";

    //Formats the cost and total cost.
    stringstream costStream;
    costStream << fixed
               << setprecision(2)
               << setfill( '0' ) << getCost();
    text += "Total Cost: $" + costStream.str();

    text += "\n\t- Quantity: x" + to_string(getQuantity());
    text += "\n";

    return text;
}