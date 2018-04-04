/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Order.cpp
//
// Created By: Bryan J Muscedere
// Date: 7/21/2016
//
// Class that represents an order. This holds a number of different
// sandwiches and allows users to purchase their order and calculates
// the total cost based on the recipes being referenced.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Order.h"

using namespace std;

/**
 * Constructor that creates an order for a certain
 * person.
 * @param name The name of the person for the order.
 */
Order::Order(std::string name) : name(name) {
    sandwiches = vector<Sandwich*>();
    totalCost = 0;
}

/**
 * Destructor which deletes all sandwiches in the order.
 */
Order::~Order() {
    for (int i = 0; i < sandwiches.size(); i++)
        delete sandwiches.at(i);
}

/**
 * Adds a new sandwich to the order.
 * @param item The sandwich being added.
 * @return The position of the sandwich.
 */
int Order::addSandwich(Sandwich* item){
    //Adds the sandwich to the list.
    sandwiches.push_back(item);
    updateTotalCost();

    return sandwiches.size() - 1;
}

/**
 * Removes a sandwich from the order.
 * @param sandwichNum The number of sandwich to remove.
 */
void Order::removeSandwich(int sandwichNum){
    //Removes the sandwich at the item pos.
    if (sandwichNum < 0 || sandwichNum >= sandwiches.size())
        return;

    //Erases the item.
    sandwiches.at(sandwichNum);
    sandwiches.erase(sandwiches.begin() + sandwichNum);
}

/**
 * Makes the order.
 * @return Whether the order can be created.
 */
bool Order::makeOrder() {
    //Check if we can make the sandwich.
    for (int i = 0; i < sandwiches.size(); i++){
        if (!sandwiches.at(i)->canMake()) return false;
    }

    //Makes the sandwich.
    for (int i = 0; i < sandwiches.size(); i++){
        sandwiches.at(i)->make();
    }

    //Notes that the order has been made.
    return true;
}

/**
 * Gets the total cost of the order.
 * @return The total cost of the order.
 */
float Order::getTotalCost() {
    return totalCost;
}

/**
 * Gets all sandwiches referenced in the order.
 * @return The sandwiches in the order.
 */
vector<Sandwich*> Order::getSandwiches(){
    return sandwiches;
}

/**
 * Prints the order details.
 * @return String containing the order details.
 */
string Order::printOrder() {
    string orderText = name + " has made the following order:\n";
    for (int i = 0; i < sandwiches.size(); i++){
        orderText += "\t-" + sandwiches.at(i)->print() + "\n";
    }

    return orderText;
}

/**
 * Updates the total cost variable.
 * This holds the total cost of the order.
 */
void Order::updateTotalCost() {
    //Iterate through all the sandwiches and update cost.
    totalCost = 0.0;
    for (int i = 0; i < sandwiches.size(); i++){
        totalCost += sandwiches.at(i)->getTotalCost();
    }
}