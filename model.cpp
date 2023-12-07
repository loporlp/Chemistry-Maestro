/*
 * Assignment 9: Chemistry Maestro
 * Class Author(s): Andrew Wilhelm, Allison Walker,
 * Mason Sansom, AJ Kennedy, Brett Baxter
 * Course: CS 3505
 * Fall 2023
 *
 * model source
 *
 * Brief:
 * All model / back end logic.
 *
*/

#include "model.h"

model::model(QObject *parent)
    : QObject{parent}
{
    // setup the model vectors
    populateRecipes();
    populateProducts();
}

/**
 * @brief model::populateRecipes - Fills the recipies vector with recipes unique to each level.
 */
void model::populateRecipes()
{
    // Order Matters!
    // Level 1
    std::vector<element> water;
    water.push_back(element::H);
    water.push_back(element::H);
    water.push_back(element::O);
    levelRecipes.push_back(water);
    // Level 2
    std::vector<element> stannousChloride;
    stannousChloride.push_back(element::Cl);
    stannousChloride.push_back(element::Cl);
    stannousChloride.push_back(element::Sn);
    levelRecipes.push_back(stannousChloride);
    // Level 3
    std::vector<element> saltpetre;
    saltpetre.push_back(element::O);
    saltpetre.push_back(element::O);
    saltpetre.push_back(element::O);
    saltpetre.push_back(element::N);
    saltpetre.push_back(element::K);
    levelRecipes.push_back(saltpetre);
    // Level 4
    std::vector<element> sulfiricAcid;
    sulfiricAcid.push_back(element::H);
    sulfiricAcid.push_back(element::H);
    sulfiricAcid.push_back(element::O);
    sulfiricAcid.push_back(element::O);
    sulfiricAcid.push_back(element::O);
    sulfiricAcid.push_back(element::O);
    sulfiricAcid.push_back(element::S);
    levelRecipes.push_back(sulfiricAcid);
    // Other recipes for more levels...
}

void model::populateProducts()
{
    // Level 1
    levelProducts.push_back(molecule::Water);
    // Level 2
    levelProducts.push_back(molecule::StannousChloride);
    // Level 3
    levelProducts.push_back(molecule::Saltpetre);
    // Level 4
    levelProducts.push_back(molecule::SulfuricAcid);
    // Other products for more levels...
}

/**
 * @brief model::checkForCombination - Sorts the reference array and the elements in scene array so they should be identical.
 * Iterates through each entry to check if they are the same, if they are not identical, return, doing nothing. If they are identical
 * send a signal to the view with the proper molecule to create.
 */
void model::checkForCombination()
{
    // Sort elements in scene array so that a successful combo can be detected.
    std::sort(elementsInScene.begin(), elementsInScene.end());

    // for each element in the current level recipe
    for(unsigned int i = 0; i < levelRecipes[levelIndex].size(); i++)
    {
        // If the elements are not equal, return.
        if(levelRecipes[levelIndex][i] != elementsInScene[i])
        {
            return;
        }
    }
    // If all of the elements are equal, emit a signal to the view.
    emit successfulCombination();
}

/**
 * @brief model::onCreateElement - Called when a element button is pressed in the view.
 * Adds the new element to the elements in scene vector and checks if a combination is possible.
 * @param index - The element reference index.
 */
void model::onCreateElement(element newElement)
{
    elementsInScene.push_back(newElement);
    // If the amount of elements in the scene matches the level recipe count, check for a combination.
    if(levelRecipes[levelIndex].size() == elementsInScene.size())
    {
        checkForCombination();
    }
}

/**
 * @brief model::onUpdateLevel - When a level updates, the level index is changed.
 * @param index - The new level index.
 */
void model::onUpdateLevel(int index)
{
    levelIndex = index;
}

/**
 * @brief model::onClearScene - Clears the elements in scene vector.
 */
void model::onClearScene()
{
    elementsInScene.clear();
}
