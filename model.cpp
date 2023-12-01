#include "model.h"
#include "QDebug"
#include <algorithm>

model::model(QObject *parent)
    : QObject{parent}
{
    populateRecipes();
}

/**
 * @brief model::populateRecipes - Fills the recipies vector with recipes unique to each level.
 */
void model::populateRecipes(){
    std::vector<element> water;
    water.push_back(element::O);
    water.push_back(element::H);
    water.push_back(element::O);
    levelRecipes.push_back(water);
    qDebug() << "added water to recipes";
}

/**
 * @brief model::checkForCombination - Sorts the reference array and the elements in scene array so they should be identical.
 * Iterates through each entry to check if they are the same, if they are not identical, return, doing nothing. If they are identical
 * send a signal to the view with the proper molecule to create.
 */
void model::checkForCombination(){
    // Sort both arrays so that if they are identical they can be checked sequentially.
    // these sorts give seg faults :)
//    std::sort(levelRecipes[levelIndex].begin(), levelRecipes[levelIndex].end());
//    std::sort(elementsInScene.begin(), elementsInScene.end());

    // for each element in the current level recipe
    for(unsigned int i = 0; i < levelRecipes[levelIndex].size(); i++){
        // If the elements are not equal, return.
        if(levelRecipes[levelIndex][i] != elementsInScene[i]){
            qDebug() << "unsuccessful combo";
            return;
            // or if we want a game over state emit a signal to do just that.
        }
    }
    // If all of the elements are equal, emit a signal to the view with the level product.
    emit successfulCombination(levelProducts[levelIndex]);
}

/**
 * @brief model::onCreateElement - Called when a element button is pressed in the view.
 * Adds the new element to the elements in scene vector and checks if a combination is possible.
 * @param index - The element reference index.
 */
void model::onCreateElement(element newElement){
    qDebug() << "pushing back element";
    elementsInScene.push_back(newElement);
    qDebug() << "recipes size: " << levelRecipes[levelIndex].size() << "elements in scene: " << elementsInScene.size();
    // If the amount of elements in the scene matches the level recipe count, check for a combination.
    if(levelRecipes[levelIndex].size() == elementsInScene.size()){
        qDebug() << "checking for combo";
        checkForCombination();
    }
}

/**
 * @brief model::onUpdateLevel - When a level updates, the level index is changed.
 * @param index - The new level index.
 */
void model::onUpdateLevel(int index){
    levelIndex = index;
    qDebug() << "level: " << index + 1;
}

/**
 * @brief model::onClearScene - Clears the elements in scene vector.
 */
void model::onClearScene(){
    elementsInScene.clear();
    qDebug() << "scene cleared";
}
