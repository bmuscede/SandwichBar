/////////////////////////////////////////////////////////////////////////////////////////////////////////
// SandwichBar.cpp
//
// Created By: Bryan J Muscedere
// Date: 7/21/2016
//
// Class that manages the SandwichBar. Handles the commands, takes
// orders, and simulates the operation of a sandwich bar.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SandwichBar.h"
#include "Capital/ComplexRecipe.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <functional>

using namespace std;

/** Random Function */
//std::default_random_engine generator;
//std::uniform_int_distribution<int> distribution(0, RAND_MAX);
//auto dice = std::bind(distribution, generator);

/**
 * Static global variable to count
 * the number of recipes and ingredient objects.
 *
 * Used for testing with Grok.
 */
int SandwichBar::numItems = 0;

/**
 * Constructor to create a default
 * sandwich bar.
 */
SandwichBar::SandwichBar() {
    setupBar(DEFAULT_NAME, DEFAULT_FUNDS);
}

/**
 * Creates a sandwich bar
 * with a set name and funds
 * @param name The sandwich bar name.
 * @param funds The sandwich bar funds.
 */
SandwichBar::SandwichBar(string name, float funds) {
    setupBar(name, funds);
}

/**
 * Destructor to delete a sandwich
 * bar instance.
 */
SandwichBar::~SandwichBar() {
    //First, deletes the recipes.
    for (int i = 0; i < recipeList->size(); i++)
        delete recipeList->at(i);
    delete recipeList;

    //Next, deletes the inventory.
    delete inventory;
}

/**
 * Runs the main portion of the program.
 * Takes in commands from the user and
 * performs the appropriate action.
 */
void SandwichBar::handleCommands() {
    string line;

    //Start by printing the header.
    printHeader();

    //Iterate until the stop command is reached.
    bool iterate = true;
    while(iterate){
        //Places a new line.
        cout << endl;

        //Prompt for input.
        cout << username << " > ";
        getline(cin, line);

        //Check commands
        if (line.compare(HELP) == 0){
            printHelp();
        } else if (line.compare(SIM) == 0) {
            int orders = -1;
            string line;

            //Prompt the user for number of orders.
            while (orders < 1 || orders > ORD_MAX) {
                cout << "Enter the number of orders to simulate: ";
                getline(cin, line);

                try {
                    orders = stoi(line);
                } catch (...) {
                    cout << "Invalid simulation value." << endl;
                }

            }

            simulate(orders);
        } else if (line.compare(ORD) == 0) {
            takeOrder();
        } else if (line.compare(INV) == 0) {
            cout << inventory->getInventoryDetails();
        } else if (line.compare(RECIPES) == 0) {
            cout << getRecipes();
        } else if (line.compare(LOOKUP) == 0) {
            lookup();
        } else if (line.compare(ADD_R) == 0) {
            addRecipe();
        } else if (line.compare(ADD_I) == 0) {
            addIngredient();
        } else if (line.compare(DETS) == 0) {
            printDetails();
        } else if (line.compare(CHANGE) == 0){
            changeName();
        } else if (line.compare(LOAD) == 0) {
            load();
        } else if (line.compare(EXIT) == 0) {
            iterate = false;
        } else if (line.compare("") == 0) {
            continue;
        } else {
            //Default case.
            cout << line << ": command not recognized." << endl;
        }
    }
}

/**
 * Sets up a sandwich bar with a desired
 * name and funds. Prepares the ingredients
 * and inventory.
 * @param name Sandwich bar name.
 * @param funds Sandwich bar funds.
 */
void SandwichBar::setupBar(string name, float funds) {
    //Sets the name and funds.
    this->name = name;
    this->funds = funds;

    //Gets the user logged in.
    try {
        struct passwd *pass;
        pass = getpwuid(getuid());
        username = pass->pw_name;
    } catch(exception& e){
        //If the lookup fails.
        username = "user";
    }

    //Loads in the recipe list and inventory.
    recipeList = new vector<Recipe*>();
    inventory = new Inventory();
}

/**
 * Prints a help dialog which contains information
 * about the available commands that can be used.
 */
void SandwichBar::printHelp(){
    //Prints the help text.
    cout << "Sample C++ program that is used to demonstrate how a " <<
         endl << "sandwich bar would work. The program allows for complex " <<
         endl << "orders and recipes." <<
         endl << endl << "Available Commands:" <<
         endl << "simulate : Simulates the entire bar for a set number of orders." <<
         endl << "order : Prepares an order of a set of sandwiches." <<
         endl << "inventory : Displays the inventory and quantities." <<
         endl << "recipes : Displays the collection of recipes." <<
         endl << "lookup : Lookup a recipe or ingredient for details." <<
         endl << "add recipe : Add a new recipe." <<
         endl << "add ingredient : Add a new ingredient." <<
         endl << "details : Displays sandwich bar name and funds." <<
         endl << "change name : Updates sandwich bar name." <<
         endl << "load : Loads in a collection of recipes and ingredients." <<
         endl << "quit : Exits the program." << endl;
}

/**
 * Simulates sandwich bar operation
 * for a desired number of orders.
 * @param numOrders The number of orders to simulate.
 */
void SandwichBar::simulate(int numOrders) {
    //Seeds the random number generator.
    srand (time(NULL));

    //Get the number of recipes.
    if (recipeList->size() == 0){
        cout << "Error: Too few recipes to simulate." << endl;
        return;
    }

    //Start by iterating through the orders.
    for (int i = 0; i < numOrders; i++){
        //First, generates an order.
        Order* currentOrder = generateRandOrder();

        //Now, we print it.
        cout << currentOrder->printOrder() << endl;

        //Perform order logic.
        if (currentOrder->makeOrder()){
            cout << "Order was successful.\n";

            if (i + 1 < numOrders)
                cout << endl;
        } else {
            cout << "Not enough ingredients are available. Ordering more...\n" << endl;

            //Order more. And then order again.
            if (!orderMore(currentOrder)){
                cout << name + " has gone bankrupt!\n" << endl;
                return;
            } else {
                cout << "Order was successful.\n";

                if (i + 1 < numOrders)
                    cout << endl;
            }

            currentOrder->makeOrder();
        }

        //Receive payment.
        funds += currentOrder->getTotalCost();
        delete currentOrder;
    }
}

/**
 * Walks a user through a standard order.
 * Prepares the order, makes it and takes
 * the user's money.
 */
void SandwichBar::takeOrder() {
    string person;

    //First, asks for their name.
    cout << "Welcome to " + name + "! What is your name?" << endl << "\t";
    getline(cin, person);

    //Creates the order object.
    Order* current = new Order(person);
    cout << "Hi, " + person + "! ";

    //Starts the main order loop.
    bool ordering = true;
    while (ordering){
        cout << "What would you like?" << endl << "\t";

        //Gets the line of the user.
        string sandwich;
        getline(cin, sandwich);

        //Looks up the recipe.
        Recipe* currentRecipe = findRecipe(sandwich);

        //Checks if we found it.
        if (currentRecipe == NULL){
            cout << "Sorry, we don't have that." << endl;
        } else {
            //See if we have any substitutions.
            cout << "Would you like to substitute anything? (Y/N)" << endl << "\t";
            string yn;
            getline(cin, yn);
            if (yn.compare("y") == 0 || yn.compare("Y") == 0){
                cout << "Alright, say \"add\" or \"remove\""
                     << " followed by an ingredient. Say \"end\" when done."
                     << endl;

                //Iterates through getting the substitutions.
                Substitution* subList = new Substitution();
                bool subLoop = true;
                while (subLoop){
                    string command;
                    cout << "\t";
                    getline(cin, command);

                    //Check which command we activated.
                    if (strncmp(command.c_str(), "add", strlen("add")) == 0){
                        string ingType = command.substr(4, command.length() - 4);
                        if (currentRecipe->containsIngredient(ingType)){
                            cout << "This recipe already has that." << endl;
                            continue;
                        }

                        //Now, gets the ingredient.
                        Ingredient* ing = inventory->getIngredient(ingType);
                        if (ing != NULL){
                            subList->addAddition(ing);
                        } else {
                            cout << "Sorry, we don't have that ingredient." << endl;
                        }
                    } else if (strncmp(command.c_str(), "remove", strlen("remove")) == 0){
                        string ingType = command.substr(7, command.length() - 7);
                        if (!currentRecipe->containsIngredient(ingType)){
                            cout << "This recipe does not have that." << endl;
                            continue;
                        }

                        //Now, gets the ingredient.
                        Ingredient* ing = inventory->getIngredient(ingType);
                        if (ing != NULL){
                            subList->addRemoval(ing);
                        } else {
                            cout << "Sorry, we don't have that ingredient." << endl;
                        }
                    } else if (strncmp(command.c_str(), "end", strlen("end")) == 0){
                        subLoop = false;
                    } else {
                        cout << "That is not a valid command!" << endl << "\t";
                    }
                }

                current->addSandwich(new Sandwich(currentRecipe, subList));
            } else {
                current->addSandwich(new Sandwich(currentRecipe));
            }

            //Now, we ask if they want anything else.
            cout << "Anything else? (Y/N)" << endl << "\t";
            getline(cin, yn);
            if (yn.compare("y") != 0 && yn.compare("Y") != 0){
                ordering = false;
            }
        }
    }

    //Prepare order.
    cout << "Alright, your order comes to $"
         << fixed
         << setprecision(2)
         << setfill( '0' ) << current->getTotalCost()
         << endl;
    if (!current->makeOrder()){
        cout << "Sorry, we are out of ingredients." << endl;
    } else {
        funds += current->getTotalCost();
        cout << "Have a great day, " << person << "!" << endl;
    }

    //Deletes the order at the end of the day.
    delete current;
}

/**
 * Prepares a string containing information on
 * all recipes in the system.
 * @return String with recipe information.
 */
string SandwichBar::getRecipes() {
    string recipeText = "RECIPE DETAILS\n";
    recipeText += "----------------------------------\n";

    //Check if we have any recipes.
    if (recipeList->size() == 0){
        recipeText += "No recipes are present.\n";
        return recipeText;
    }

    for (int i = 0; i < recipeList->size(); i++){
        recipeText += recipeList->at(i)->print();
    }

    return recipeText;
}

/**
 * Looks up a recipe or ingredient
 * based on a user's input. Searches
 * through both recipe lists and
 * inventory lists.
 */
void SandwichBar::lookup(){
    string line;

    //Get the item to lookup.
    cout << "Enter an ingredient or recipe: ";
    getline(cin, line);

    //With this, start by looking at ingredients.
    Ingredient* ing = inventory->getIngredient(line);
    if (ing != NULL) {
        cout << ing->printDetails();
        return;
    }

    //Otherwise, find a recipe.
    Recipe* rec = findRecipe(line);
    if (rec != NULL){
        cout << rec->printDetails();
        return;
    }

    //Otherwise, notify that the item doesn't exist.
    cout << "That item does not exist!" << endl;
}

/**
 * Adds a new recipe to the recipe list
 * based on the user's input. Uses helper
 * methods to parse the input.
 */
void SandwichBar::addRecipe(){
    //Prompt the user in the form of a schema.
    cout << "Enter your recipes in the form of:" << endl
         << "\tsimple,<name>,<price>,<{ingredients}>" << endl
         << "\t-OR-" << endl << "\tcomplex,<name>,"
         <<   "<base name>,<price>,{<add ingredients>}, {<remove ingredients>}" << endl
         << "Type end to finish." << endl;

    //Now, we iterate until we encounter end.
    bool loop = true;
    while (loop){
        string line;
        getline(cin, line);

        //Check for end condition.
        if (line.compare("end") == 0){
            loop = false;
            continue;
        }

        //Perform the addition.
        string msg;
        bool success = addRecipeLine(line, &msg);
        if (!success){
            //Print error message.
            cout << "\t" << msg << endl;
        }
    }
}

/**
 * Adds a new ingredient to the inventory
 * based on the user's input. Uses helper
 * methods to parse the input.
 */
void SandwichBar::addIngredient(){
    //Prompt the user in the form of a schema.
    cout << "Enter your ingredients in the form of:" << endl
         << "\tsimple,<name>,<price>,<quantity>" << endl
         << "\t-OR-" << endl << "\tcomplex,<name>,<price>,<quantity>,{<ingredients>}" << endl
         << "Type end to finish." << endl;

    //Now, we iterate until we encounter end.
    bool loop = true;
    while (loop){
        string line;
        getline(cin, line);

        //Check for end condition.
        if (line.compare("end") == 0){
            loop = false;
            continue;
        }

        //Perform the addition.
        string msg;
        bool success = addIngredientLine(line, &msg);
        if (!success){
            //Print error message.
            cout << "\t" << msg << endl;
        }
    }
}

/**
 * Prints information about the name
 * and funds of the sandwich bar.
 */
void SandwichBar::printDetails(){
    cout << name << endl;
    cout << "Your funds: $" << fixed
         << setprecision(2)
         << setfill( '0' ) << funds
         << endl;
}

/**
 * Changes the name of the sandwich
 * bar to what the user would like.
 */
void SandwichBar::changeName(){
    cout << "Enter your new Sandwich Bar name: ";

    //Get the input.
    string line;
    getline(cin, line);

    //Check for invalid name.
    if (line.compare("") == 0){
        cout << "Invalid name.";
    }

    //Otherwise, change it.
    cout << "You are now " << line << "." << endl;
    name = line;
}

/**
 * Driver method that loads in
 * a file and creates the specified
 * ingredients, recipes, and name
 * of the sandwich bar.
 */
void SandwichBar::load() {
    string line;
    int lineNum = 0;
    bool barFlag = false;
    bool ingFlag = false;
    bool recipeFlag = false;
    bool alreadyBar = false;
    bool error = false;

    //Asks the user for a file name.
    string filename;
    cout << "Enter filename to load: ";
    getline(cin, filename);

    //Loads the file.
    ifstream loadStream;
    loadStream.open(filename);
    if (loadStream.is_open()) {
        while (getline (loadStream,line)){
            lineNum++;

            //Checks for blank characters.
            if ((line.compare(0, 2, "//") == 0) || line.empty())
                continue;

            //Checks what line we are dealing with.
            if (line.compare(BAR_FLAG) == 0){
                //Perform sanity check.
                if (barFlag == true) {
                    cout << "Error on line " << lineNum
                         << ": BAR command already encountered." <<endl;
                    error = true;
                    break;
                }

                barFlag = true;
            } else if (line.compare(ING_FLAG) == 0){
                //Perform sanity check.
                if (barFlag != true){
                   cout << "Error on line " << lineNum
                        << ": BAR command comes first." << endl;
                    error = true;
                    break;
                } else if (ingFlag == true){
                    cout << "Error on line " << lineNum
                         << ": INGREDIENT command already encountered." <<endl;
                    error = true;
                    break;
                }

                ingFlag = true;
            } else if (line.compare(RECIPE_FLAG) == 0) {
                //Perform sanity check.
                if (barFlag != true){
                    cout << "Error on line " << lineNum
                         << ": BAR command comes first." << endl;
                    error = true;
                    break;
                } else if (ingFlag != true){
                    cout << "Error on line " << lineNum
                         << ": INGREDIENT command comes first." <<endl;
                    error = true;
                    break;
                } else if (recipeFlag == true){
                    cout << "Error on line " << lineNum
                         << ": RECIPE command already encountered." <<endl;
                    error = true;
                    break;
                }

                recipeFlag = true;
            } else if (recipeFlag == true) {
                //Parse the line.
                string msg;
                bool succ = addRecipeLine(line, &msg);

                //Check for errors.
                if (!succ){
                    cout << "Error on line " << lineNum
                         << ": " << msg << endl;
                    error = true;
                    break;
                }
            } else if (ingFlag == true) {
                //Parse the line.
                string msg;
                bool succ = addIngredientLine(line, &msg);

                //Check for errors.
                if (!succ){
                    cout << "Error on line " << lineNum
                         << ": " << msg << endl;
                    error = true;
                    break;
                }
            } else if (barFlag == true) {
                //Parse the bar information.
                vector<string>* tokens = tokenize(line);

                //Check for sanity.
                if (alreadyBar == true){
                    cout << "Error on line " << lineNum
                        << ": BAR information already set." << endl;
                    error = true;

                    delete tokens;
                    break;
                } else if (tokens->size() != 2) {
                    cout << "Error on line " << lineNum
                        << ": Invalid BAR command." <<endl;

                    delete tokens;
                    break;
                }

                //Read in the bar name.
                name = tokens->at(0);
                funds = stof(tokens->at(1));

                //Delete the tokens.
                alreadyBar = true;
                delete tokens;
            } else {
                cout << "Unknown error encountered at line " << lineNum << "." << endl;
                error = true;
                break;
            }
        }

        //Deals with the end.
        loadStream.close();

        //Prints the results.
        if (error) {
            cout << "Load aborted!" << endl;
        } else {
            cout << name << " is now in business!" << endl;
        }
    } else {
        cout << "File could not be opened!" << endl;
    }
}

/**
 * Prints the header that is shown when the
 * program is started.
 */
void SandwichBar::printHeader(){
    string header = "------------------------------------------------------\n";
    header += "| Sandwich Bar v0.1                                  |\n";
    header += "| C++ Version                                        |\n";
    header += "|                                                    |\n";
    header += "| University of Waterloo, 2016                       |\n";
    header += "------------------------------------------------------\n";

    //Prints the header.
    cout << header;
}

/**
 * Helper method which takes a string and tokenizes it
 * based on a comma.
 * @param line The line to tokenize.
 * @return A vector with all the string tokens.
 */
vector<string>* SandwichBar::tokenize(string line) {
    vector<string>* tokens = new vector<string>();

    //Copies the line into a c string.
    char* cLine = new char[line.length() + 1];
    strcpy(cLine, line.c_str());

    //Iterates through the tokens.
    char* current = strtok(cLine, ",");
    while(current != NULL){
        string item(current);
        tokens->push_back(item);

        current = strtok(NULL, ",");
    }

    delete[] cLine;
    delete[] current;

    return tokens;
}

/**
 * Generates a randomized order for one customer.
 * Prepares a random number of sandwiches and
 * a random number of substitutions.
 * @return A pointer to the generated order.
 */
Order* SandwichBar::generateRandOrder() {
    int nameIndex = /*dice()*/10 % names->length();

    //First, generate random name.
    string orderee = names[nameIndex];
    Order* randomOrder = new Order(orderee);

    //Now decides the number of sandwiches.
    int numSand = /*dice()*/10 % SAND_MAX + 1;

    //Generates a random sandwich.
    for (int i = 0; i < numSand; i++){
        randomOrder->addSandwich(generateRandSandwich());
    }

    return randomOrder;
}

/**
 * Helper method which generates a random sandwich
 * for the random order.
 * @return A pointer to the generated random sandwich.
 */
Sandwich* SandwichBar::generateRandSandwich(){
    //First, we select a random recipe.
    int recipeIndex = /*dice()*/10 % recipeList->size();
    Recipe* decidedRecipe = recipeList->at(recipeIndex);

    //Now we decide if we need a substitution.
    int oddEven = /*dice()*/10 % 4;
    if (oddEven % 2){
        return new Sandwich(decidedRecipe);
    }

    //Generate a substitution.
    Substitution* substitution = new Substitution();
    vector<Ingredient*> ingredients = decidedRecipe->getIngredients();
    uniform_int_distribution<int> ingGen(0, ingredients.size());

    //Goes through and substitutes.
    int numSubs = /*dice()*/10 % SUB_MAX + 1;
    for (int i = 0; i < numSubs; i++){
        oddEven = /*dice()*/10 % 4;

        //Add a substitution.
        if (oddEven % 2){
            //We loop until the ingredient is there.
            bool bad = true;
            while(bad){
                Ingredient* ing = inventory->getRandomIngredient();
                vector<Ingredient*> adds = substitution->getAdditions();

                //Sees if the ingredient exists.
                if (find(ingredients.begin(), ingredients.end(), ing)
                    == ingredients.end() && find(adds.begin(), adds.end(), ing) ==
                                            adds.end()){
                    bad = false;
                    substitution->addAddition(ing);
                }
            }
        } else {
            //Pick a random ingredient to remove.
            bool bad = true;
            while (bad){
                Ingredient* removed = ingredients.at(/*dice()*/10 % ingredients.size());

                vector<Ingredient*> removes = substitution->getRemovals();
                if (find(removes.begin(), removes.end(), removed) ==
                    removes.end()){
                    bad = false;
                    substitution->addRemoval(removed);
                }
            }
        }
    }

    return new Sandwich(decidedRecipe, substitution);

}

/**
 * Helper method that orders more ingredients for all the items
 * in the order. Allows ingredients to never run out when simulating
 * the sandwich bar.
 * @param currentOrder The order being simulated.
 * @return A boolean indicating success.
 */
bool SandwichBar::orderMore(Order* currentOrder){
    //Get the ingredients.
    vector<Sandwich*> sandwiches = currentOrder->getSandwiches();
    for (int i = 0; i < sandwiches.size(); i++){
        vector<Ingredient*> ingredients = sandwiches.at(i)->getRecipe().getIngredients();

        //We now iterate through the ingredients for that recipe.
        for (int j = 0; j < ingredients.size(); j++){
            if (funds < ING_FACTOR * ingredients.at(j)->getCost()){
                return false;
            }

            //Update the funds and order more.
            funds -= ING_FACTOR * ingredients.at(j)->getCost();
            ingredients.at(j)->orderMore(ING_FACTOR);
        }

        //Next, we iterate through the sandwich additions.
        if (sandwiches.at(i)->hasSubstitution()) {
            ingredients = sandwiches.at(i)->getSubstitution().getAdditions();
            for (int j = 0; j < ingredients.size(); j++){
                if (funds < ING_FACTOR * ingredients.at(j)->getCost()){
                    return false;
                }

                //Update the funds and order more.
                funds -= ING_FACTOR * ingredients.at(j)->getCost();
                ingredients.at(j)->orderMore(ING_FACTOR);
            }
        }
    }

    return true;
}

/**
 * Adds an ingredient to the inventory
 * based on some line of text.
 * @param line The line to add.
 * @param msg A string that will have an error message returned.
 * @return A boolean indicating success.
 */
bool SandwichBar::addIngredientLine(string line, string* msg){
//Parse the ingredients.
    vector<string>* tokens = tokenize(line);

    //Check type of ingredient.
    if (tokens->at(0).compare(SIMPLE) == 0){
        //Perform sanity check.
        if (tokens->size() != 4) {
            *msg = "Invalid INGREDIENT command.";

            delete tokens;
            return false;
        }

        //Adds in the ingredient.
        inventory->addSimpleIngredient(tokens->at(1),
                                       stoi(tokens->at(3)), stof(tokens->at(2)));
    } else if (tokens->at(0).compare(COMPLEX) == 0) {
        //Perform sanity check.
        if (tokens->size() < 4) {
            *msg = "Invalid INGREDIENT command.";

            delete tokens;
            return false;
        } else if (tokens->at(3).compare("{}") == 0
                   || tokens->at(3).compare("{ }") == 0){
            *msg = "Invalid INGREDIENT command.";

            delete tokens;
            return false;
        }

        //Next, parses the subcommands.
        vector<Ingredient*>* listOfIngredients = new vector<Ingredient*>();
        for (int i = 3; i < tokens->size(); i++){
            string currentItem = tokens->at(i);

            //Removes the curly braces.
            if (i == 3){
                currentItem.erase(
                        remove(currentItem.begin(),
                               currentItem.end(), '{'), currentItem.end());
            }
            if (i == tokens->size() - 1){
                currentItem.erase(
                        remove(currentItem.begin(),
                               currentItem.end(), '}'), currentItem.end());
            }

            //Get the ingredient.
            Ingredient* current = inventory->getIngredient(currentItem);
            if (current == NULL){
                *msg = "Complex ingredient references non-existent ingredient.";

                delete tokens;
                return false;
            }
            listOfIngredients->push_back(current);
        }

        //Now, we create the ingredient.
        inventory->addComplexIngredient(tokens->at(1),
                                        stof(tokens->at(2)), listOfIngredients);
    } else {
        *msg = "Unknown ingredient command.";

        delete tokens;
        return false;
    }

    delete tokens;
    *msg = "";
    return true;
}

/**
 * Adds a recipe to the recipe list
 * based on some line of text.
 * @param line The line to add.
 * @param msg A string that will have an error message returned.
 * @return A boolean indicating success.
 */
bool SandwichBar::addRecipeLine(string line, string* msg){
    //Parse the current line for recipes.
    vector<string>* tokens = tokenize(line);

    //Check what type of recipe we have.
    if (tokens->at(0).compare(SIMPLE) == 0){
        //Perform sanity check.
        if (tokens->size() < 4){
            *msg = "Invalid RECIPE command.";

            delete tokens;
            return false;
        } else if (tokens->at(3).compare("{}") == 0
                   || tokens->at(3).compare("{ }") == 0){
            *msg = "Invalid RECIPE command.";

            delete tokens;
            return false;
        }

        //Next, parses the ingredients.
        vector<Ingredient*> recipeIngredients = vector<Ingredient*>();
        for (int i = 3; i < tokens->size(); i++) {
            string currentItem = tokens->at(i);

            //Removes the curly braces.
            if (i == 3) {
                currentItem.erase(
                        remove(currentItem.begin(),
                               currentItem.end(), '{'), currentItem.end());
            }
            if (i == tokens->size() - 1) {
                currentItem.erase(
                        remove(currentItem.begin(),
                               currentItem.end(), '}'), currentItem.end());
            }

            //Gets the referenced ingredient.
            Ingredient* current = inventory->getIngredient(currentItem);
            if (current == NULL){
                *msg = "Recipe references non-existent ingredient.";

                delete tokens;
                return false;
            }

            recipeIngredients.push_back(current);
        }

        //Creates the recipe.
        recipeList->push_back(new Recipe(tokens->at(1), recipeIngredients,
                                         stof(tokens->at(2))));
    } else if (tokens->at(0).compare(COMPLEX) == 0){
        //Perform sanity check.
        if (tokens->size() < 6){
            *msg = "Invalid RECIPE command.";

            delete tokens;
            return false;
        } else if ((tokens->at(5).compare("{}") == 0
                    || tokens->at(5).compare("{ }") == 0) &&
                   (tokens->at(4).compare("{}") == 0
                    || tokens->at(4).compare("{ }") == 0)){
            *msg = "Invalid RECIPE command.";

            delete tokens;
            return false;
        }

        //Next, we add the base recipe.
        Recipe* baseRecipe = findRecipe(tokens->at(2));
        if (baseRecipe == NULL){
            *msg = "Base recipe does not exist.";

            delete tokens;
            return false;
        }

        //Iterate through the additions.
        vector<Ingredient*> additions = vector<Ingredient*>();
        bool contAdd = true;
        int i = 4;
        string ending = "}";
        while(contAdd){
            //Check if we have a } brace.
            string currentItem = tokens->at(i);
            if (currentItem.compare(
                    currentItem.length() - ending.length(), ending.length(), ending) == 0){
                contAdd = false;
            }

            //Checks whether we have an ending.
            if (tokens->at(i).compare("{}") == 0
                || tokens->at(i).compare("{ }") == 0){
                break;
            }

            //Removes the curly braces.
            if (i == 4) {
                currentItem.erase(
                        remove(currentItem.begin(),
                               currentItem.end(), '{'), currentItem.end());
            }
            if (contAdd == false) {
                currentItem.erase(
                        remove(currentItem.begin(),
                               currentItem.end(), '}'), currentItem.end());
            }

            //Gets the referenced ingredient.
            Ingredient* current = inventory->getIngredient(currentItem);
            if (current == NULL){
                *msg = "Recipe references non-existent ingredient.";

                delete tokens;
                return false;
            }

            additions.push_back(current);
            i++;
        }

        //Iterate through the removals
        vector<Ingredient*> removals = vector<Ingredient*>();
        contAdd = true;
        bool first = true;
        while(contAdd){
            //Check if we have a } brace.
            string currentItem = tokens->at(i);
            if (currentItem.compare(
                    currentItem.length() - ending.length(), ending.length(), ending) == 0){
                contAdd = false;
            }

            //Checks whether we have an ending.
            if (tokens->at(i).compare("{}") == 0
                || tokens->at(i).compare("{ }") == 0){
                break;
            }

            //Removes the curly braces.
            if (first) {
                currentItem.erase(
                        remove(currentItem.begin(),
                               currentItem.end(), '{'), currentItem.end());
                first = false;
            }
            if (i == tokens->size() - 1) {
                currentItem.erase(
                        remove(currentItem.begin(),
                               currentItem.end(), '}'), currentItem.end());
            }

            //Gets the referenced ingredient.
            Ingredient* current = inventory->getIngredient(currentItem);
            if (current == NULL){
                *msg = "Recipe references non-existent ingredient.";

                delete tokens;
                return false;
            }

            removals.push_back(current);
            i++;
        }

        //Creates the recipe.
        recipeList->push_back(new ComplexRecipe(tokens->at(1),
                                                additions, baseRecipe,
                                                removals, stof(tokens->at(3))));
    } else {
        *msg = "Unknown RECIPE command.";

        delete tokens;
        return false;
    }

    delete tokens;
    return true;
}

/**
 * Helper method which finds a recipe by name.
 * @param recipeName The name of the recipe.
 * @return A pointer to the recipe.
 */
Recipe* SandwichBar::findRecipe(string recipeName){
    //Goes through each recipe and looks.
    for (int i = 0; i < recipeList->size(); i++){
        if (recipeName.compare(recipeList->at(i)->getName()) == 0){
            return recipeList->at(i);
        }
    }

    return NULL;
}
