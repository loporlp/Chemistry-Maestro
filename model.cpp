#include "model.h"

model::model(QObject *parent)
    : QObject{parent}
{

}

void model::populateReference(){
    elementReference.push_back(element::H);
    elementReference.push_back(element::C);
    elementReference.push_back(element::O);
}

void model::onCreateElement(int index){
    elementsInScene.push_back(elementReference[index]);
}

void model::onUpdateLevel(int index){
    levelIndex = index;
}

void model::onClearScene(){
    elementsInScene.clear();
}
