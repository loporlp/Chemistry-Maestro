/*
 * Assignment 9: Chemistry Maestro
 * Class Author(s): Andrew Wilhelm, Allison Walker,
 * Mason Sansom, AJ Kennedy, Brett Baxter
 * Course: CS 3505
 * Fall 2023
 *
 * mainwindow header
 *
 * Brief:
 * All view / UI logic.
 *
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Header Includes
#include "model.h"
#include "ui_mainwindow.h"

// Q Includes
#include <QMainWindow>
#include <QStackedWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QDialog>
#include <QGroupBox>
#include <QTimer>
#include <QDebug>

// Other Includes
#include <Box2D/Box2D.h>
#include <stdio.h>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(model& model, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Box2D Variables
    b2Body *body;
    b2World world;
    std::vector<QLabel *> bodyDisplays;
    std::vector<b2Body *> bodies;
    bool bodiesLocked;

    // Level Tracking
    int32 currentLevel;
    int32 completedLevels;

    // View Setup Methods
    void setupStartScreen();
    void setupGameScreen();
    void setLabelVisible(bool visible);
    // Model Setup Methods
    void setupModel(model& model);

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

    void onSuccessfulCombination();

    void resetLevelData(int32 newLevelValue);
    void resetLevelData();
    void addBody(QString imgPath, float32 scale);
    void addMolecule(QString imgPath);

    void updateWorld(float32 timeStep, int32 velocityIterations, int32 positionIterations);

signals:
    void positionChanged(int ax, int ay);
    void createElement(element newElement);
    void clearScene();
    void updateLevel(int index);

};
#endif // MAINWINDOW_H
