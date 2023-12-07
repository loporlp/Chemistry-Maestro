/*
 * Assignment 9: Chemistry Maestro
 * Class Author(s): Andrew Wilhelm, Allison Walker,
 * Mason Sansom, AJ Kennedy, Brett Baxter
 * Course: CS 3505
 * Fall 2023
 *
 * model header
 *
 * Brief:
 * All model / back end logic.
 *
*/

#ifndef MODEL_H
#define MODEL_H

// Header Includes
#include "enums.h"

// Q Includes
#include <QObject>

// Other Includes
#include <algorithm>
#include <vector>

class model : public QObject
{
    Q_OBJECT
public:
    explicit model(QObject *parent = nullptr);

private:
    int levelIndex;

    // Elements currently in the scene. Clears after every level change or clear button press.
    std::vector<element> elementsInScene;

    // access into this by using levelIndex.
    // A vector of vectors with elements for the solution to each level.
    std::vector<std::vector<element>> levelRecipes;

    // access into this by using levelIndex.
    // A vector of molecules that correspont to the solution for each level.
    std::vector<molecule> levelProducts;

    // Model Methods
    void populateRecipes();
    void populateProducts();
    void checkForCombination();

public slots:
    void onCreateElement(element newElement);
    void onUpdateLevel(int levelIndex);
    void onClearScene();

signals:
    void successfulCombination();

};

#endif // MODEL_H
