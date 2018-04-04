cmake_minimum_required(VERSION 3.5)
project(Sandwich_Bar)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SandwichBar.cpp
        FoodItems/Ingredient.cpp Customers/Sandwich.cpp Customers/Order.cpp Capital/Recipe.cpp
        FoodItems/Inventory.cpp Customers/Substitution.cpp Customers/Substitution.h
        FoodItems/SimpleIngredient.cpp FoodItems/SimpleIngredient.h FoodItems/Food.cpp
        FoodItems/Food.h FoodItems/ComplexIngredient.cpp FoodItems/ComplexIngredient.h
        Capital/ComplexRecipe.cpp
        Capital/ComplexRecipe.h)
add_executable(SandwichBar ${SOURCE_FILES})

#FOR USE WITH GROK PIPELINE
set_target_properties(SandwichBar PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
