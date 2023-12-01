#include "model.h"
#include "QDebug"
#include <algorithm>

model::model(QObject *parent)
    : QObject{parent}
{
    populateRecipes();
}

void model::populateRecipes(){

}

void model::checkForCombination(){
    // Sort both arrays so that if they are identical they can be checked sequentially.
    std::sort(levelRecipes[levelIndex].begin(), levelRecipes[levelIndex].end());
    std::sort(elementsInScene.begin(), elementsInScene.end());

    // for each element in the current level recipe
    for(unsigned int i = 0; i < levelRecipes[levelIndex].size(); i++){
        // If the elements are not equal, return.
        if(levelRecipes[levelIndex][i] != elementsInScene[i]){
            return;
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
    elementsInScene.push_back(newElement);
    // If the amount of elements in the scene matches the level recipe count, check for a combination.
    if(levelRecipes[levelIndex].size() == elementsInScene.size()){
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
