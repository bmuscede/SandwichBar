/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ComplexIngredient.h
//
// Created By: Bryan J Muscedere
// Date: 7/22/2016
//
// Dictates how a complex ingredient operates. Allows users to use the
// ingredient. Order more instances of it, and print its details. Also
// relies on the simple ingredient to operate.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SANDWICH_BAR_COMPLEXINGREDIENT_H
#define SANDWICH_BAR_COMPLEXINGREDIENT_H

#include "Ingredient.h"

class ComplexIngredient : public Ingredient {
public:
    /** Constructor/Destructor */
    ComplexIngredient(std::string name,
                      float premium, std::vector<Ingredient*>* basedOn);
    virtual ~ComplexIngredient();

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
    float premium;
    std::vector<Ingredient*>* basedOn;
};


#endif //SANDWICH_BAR_COMPLEXINGREDIENT_H
