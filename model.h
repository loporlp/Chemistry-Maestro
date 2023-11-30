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

    std::vector<element> elementReference;
    std::vector<element> elementsInScene;

    // a vector of vectors with the recipe for the level.
    std::vector<std::vector<element>> levelSolutions;

    void populateReference();

public slots:
    void onCreateElement(int index);
    void onUpdateLevel(int levelIndex);
    void onClearScene();

};

#endif // MODEL_H
