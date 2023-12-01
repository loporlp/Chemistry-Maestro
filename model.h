#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <vector>
#include "enums.h"

class model : public QObject
{
    Q_OBJECT
public:
    explicit model(QObject *parent = nullptr);

private:
    int levelIndex;

    std::vector<element> elementsInScene;
    // access into this by using levelIndex.
    std::vector<std::vector<element>> levelRecipes;
    // access into this by using levelIndex.
    std::vector<molecule> levelProducts;

    // a vector of vectors with the recipe for the level.
    std::vector<std::vector<element>> levelSolutions;

    void populateRecipes();

    void checkForCombination();

public slots:
    void onCreateElement(element newElement);
    void onUpdateLevel(int levelIndex);
    void onClearScene();

signals:
    void successfulCombination(molecule product);

};

#endif // MODEL_H
