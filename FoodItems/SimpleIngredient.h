/////////////////////////////////////////////////////////////////////////////////////////////////////////
// SimpleIngredient.h
//
// Created By: Bryan J Muscedere
// Date: 7/22/2016
//
// Dictates how a simple ingredient operates. Allows users to use the
// ingredient. Order more instances of it, and print its details.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SANDWICH_BAR_SIMPLEINGREDIENT_H
#define SANDWICH_BAR_SIMPLEINGREDIENT_H


#include "Ingredient.h"

class SimpleIngredient : public Ingredient {

public:
    /** Constructor/Destructor */
    SimpleIngredient(std::string name, int quantity, float cost);
    virtual ~SimpleIngredient();

    /** Recipe Operations */
    virtual void orderMore(int amount);
    virtual float getCost();
    virtual int getQuantity();
    virtual bool canUse();
    virtual bool useIngredient();

    /** Print Methods */
    virtual std::string printDetails();

    /** Update Method */
    void updateReferences(std::vector<Food*> references);

private:
    /** Private Variables */
    int quantity;
    float cost;
};


#endif //SANDWICH_BAR_SIMPLEINGREDIENT_H
