#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "model.h"
#include <Box2D/Box2D.h>
#include <stdio.h>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(model& model, QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void positionChanged(int ax, int ay);
    void createElement(element newElement);
    void clearScene();
    void updateLevel(int index);

private slots:
    void showGameScreen();
    void restartGame();

    void showStatsPopup();
    void showHintsPopup();
    void showHowToPlayPopup();

    void onCloseButtonClicked();
    void onCloseLevelInstructionButtonClicked();

    void onClearButtonClicked();

    void onLevelButtonClicked();
    void showLevelInstructionsPopup(int selectedLevel);
    void onChemicalButtonClicked();

    void onSuccessfulCombination(molecule newMolecule);

    /**
     * @brief resetLevelData - Removes all non ground/wall bodies in the world, defaults all other level data, and
     *        sets the current level value to that of the variable.
     * @param newLevelValue - the new level to be set. If level is not intended to change,
     *        pass in the current currentLevel value.
     */
    void resetLevelData(int32 newLevelValue);
    void resetLevelData();
    void addBody(QString imgPath, float32 scale);
    void addChemical(QString imgPath);

    void updateWorld(float32 timeStep, int32 velocityIterations, int32 positionIterations);

private:
    Ui::MainWindow *ui;

    b2Body *body;
    b2World world;

    std::vector<QLabel *> bodyDisplays;
    std::vector<b2Body *> bodies;

    int32 currentLevel;
    int32 completedLevels;

    bool bodiesLocked;

    void setupStartScreen();
    void setupGameScreen();

    void setupModel(model& model);

    void setLabelVisible(bool visible);

};
#endif // MAINWINDOW_H
