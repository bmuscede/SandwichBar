/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ingredient.h
//
// Created By: Bryan J Muscedere
// Date: 7/21/2016
//
// Shell class which contains common methods between the ComplexIngredient and
// SimpleIngredient. Joins the commonalities between these two classes. This
// class cannot be initialized by itself.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SANDWICH_BAR_INGREDIENT_H
#define SANDWICH_BAR_INGREDIENT_H

#include <string>
#include <vector>
#include "Food.h"

class Ingredient : public Food {
public:
    /** Destructor */
    virtual ~Ingredient();

    /** Recipe Operations */
    virtual void orderMore(int amount) = 0;
    virtual float getCost() = 0;
    virtual int getQuantity() = 0;
    virtual bool useIngredient() = 0;
    virtual bool canUse() = 0;

    /** Print Methods */
    virtual std::string printDetails() = 0;
    std::string getName();

    /** Update Method */
    virtual void updateReferences(std::vector<Food*> references) = 0;

protected:
    /** Constructor */
    Ingredient(std::string name);

    /** Pringt Methods */
    std::string printHeader();

private:
    /** Private Variables */
    const std::string commonName;
};

#endif //SANDWICH_BAR_INGREDIENT_H
