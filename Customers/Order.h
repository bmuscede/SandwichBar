/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Order.h
//
// Created By: Bryan J Muscedere
// Date: 7/21/2016
//
// Class that represents an order. This holds a number of different
// sandwiches and allows users to purchase their order and calculates
// the total cost based on the recipes being referenced.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SANDWICH_BAR_ORDER_H
#define SANDWICH_BAR_ORDER_H

#include "Sandwich.h"
#include <string>
#include <vector>

class Order {
public:
    /** Constructor/Destructor */
    Order(std::string name);
    ~Order();

    /** Sandwich Operations */
    int addSandwich(Sandwich* item);
    void removeSandwich(int sandwichNum);

    /** Order Operations */
    bool makeOrder();
    float getTotalCost();
    std::vector<Sandwich*> getSandwiches();

    /** Print Methods */
    std::string printOrder();

private:
    /** Private Variables */
    std::string name;
    float totalCost;
    std::vector<Sandwich*> sandwiches;

    /** Helper Method */
    void updateTotalCost();
};


#endif //SANDWICH_BAR_ORDER_H
