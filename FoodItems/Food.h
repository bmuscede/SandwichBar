/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Food.h
//
// Created By: Bryan J Muscedere
// Date: 7/22/2016
//
// Master class for the recipes and ingredients in the system. Can't be
// initialized directly but keeps track of how all the items reference
// each other.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SANDWICH_BAR_FOOD_H
#define SANDWICH_BAR_FOOD_H

#include <vector>
#include <string>

class Food {
public:
    /** Destructor */
    virtual ~Food();

    /** Print Methods */
    virtual std::string getName() = 0;

    /** Update Method */
    virtual void updateReferences(std::vector<Food*> references) = 0;
protected:
    /** Constructor */
    Food();

    /** Helper Methods */
    void manageReferences();
    std::vector<Food*> getReferences();
    std::string printReferences();
    void addReferences(std::vector<Food*> references);

private:
    /** Private Variables */
    std::vector<Food*> referencedBy;
};


#endif //SANDWICH_BAR_FOOD_H
