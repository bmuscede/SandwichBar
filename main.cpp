/////////////////////////////////////////////////////////////////////////////////////////////////////////
// main.cpp
//
// Created By: Bryan J Muscedere
// Date: 7/21/2016
//
// Driver class that simply creates the sandwich bar
// and runs the commands.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "SandwichBar.h"

using namespace std;

/**
 * Main point of entry for the
 * program. Invokes the sandwich
 * bar class.
 * @return Program return code.
 */
int main() {
    //Prepare sandwich bar.
    SandwichBar bar = SandwichBar();

    //Run sandwich bar.
    bar.handleCommands();

    return 0;
}