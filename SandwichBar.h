/////////////////////////////////////////////////////////////////////////////////////////////////////////
// SandwichBar.h
//
// Created By: Bryan J Muscedere
// Date: 7/21/2016
//
// Class that manages the SandwichBar. Handles the commands, takes
// orders, and simulates the operation of a sandwich bar.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SANDWICH_BAR_SANDWICHBAR_H
#define SANDWICH_BAR_SANDWICHBAR_H

#include "Customers/Sandwich.h"
#include "Customers/Order.h"
#include "Capital/Recipe.h"
#include "FoodItems/Inventory.h"
#include <string>
#include <vector>

class SandwichBar {
public:
    /** Constructors/Destructors */
    SandwichBar();
    SandwichBar(std::string name, float funds);
    ~SandwichBar();

    /** Driver Methods */
    void handleCommands();

    /** Global Variables */
    static int numItems;

private:
    /** Private Variables */
    std::string name;
    float funds;
    std::vector<Recipe*>* recipeList;
    Inventory* inventory;
    std::string username;

    /** Command Methods */
    void setupBar(std::string name, float funds);
    void printHelp();
    void simulate(int numOrders);
    void takeOrder();
    std::string getRecipes();
    void lookup();
    void addRecipe();
    void addIngredient();
    void printDetails();
    void changeName();
    void load();

    /** Helper Methods */
    void printHeader();
    std::vector<std::string>* tokenize(std::string line);
    Order* generateRandOrder();
    Sandwich* generateRandSandwich();
    bool orderMore(Order* currentOrder);
    bool addIngredientLine(std::string line, std::string* msg);
    bool addRecipeLine(std::string line, std::string* msg);
    Recipe* findRecipe(std::string recipeName);

    /** Command Constants */
    const std::string HELP = "help";
    const std::string ORD = "order";
    const std::string INV = "inventory";
    const std::string DETS = "details";
    const std::string CHANGE = "change name";
    const std::string RECIPES = "recipes";
    const std::string SIM = "simulate";
    const std::string LOAD = "load";
    const std::string EXIT = "quit";
    const std::string ADD_I = "add ingredient";
    const std::string ADD_R = "add recipe";
    const std::string LOOKUP = "lookup";

    /** Load Flags */
    const std::string BAR_FLAG = "BAR";
    const std::string ING_FLAG = "INGREDIENT";
    const std::string RECIPE_FLAG = "RECIPE";
    const std::string SIMPLE = "simple";
    const std::string COMPLEX = "complex";

    /** Default Sandwich Bar Constants */
    const std::string DEFAULT_NAME = "Defacto's Sandwich Bar";
    const float DEFAULT_FUNDS = 1000.00;

    /** Simulation Constants */
    const int ORD_MAX = 10000;
    const int SAND_MAX = 10;
    const int SUB_MAX = 2;
    const int ING_FACTOR = 10;
    std::string names[12] = {
            "Bryan",
            "Nancy",
            "Jeff",
            "Hillary",
            "Rick",
            "Erin",
            "Greg",
            "Sarah",
            "Duncan",
            "Mabel",
            "Robbie",
            "Beth"
    };
};

#endif //SANDWICH_BAR_SANDWICHBAR_H
