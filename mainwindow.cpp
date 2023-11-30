#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QGroupBox>


MainWindow::MainWindow(model& model, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up the start screen and game screen
    setupStartScreen();
    setupGameScreen();

    setupModel(model);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setupStartScreen()
{
    // Set up start button connection
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::showGameScreen);
}


void MainWindow::setupGameScreen()
{
    ui->popupModal->setVisible(false);

    // Connect slot for the restart button
    connect(ui->restartButton, &QPushButton::clicked, this, &MainWindow::restartGame);

    // Connect slots for the Stats, Hints, and How To Play buttons
    connect(ui->statsButton, &QPushButton::clicked, this, &MainWindow::showStatsPopup);
    connect(ui->hintButton, &QPushButton::clicked, this, &MainWindow::showHintsPopup);
    connect(ui->howToPlayButton, &QPushButton::clicked, this, &MainWindow::showHowToPlayPopup);

    // Connect slot for the Clear button
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);

    // Connect slots for the Level buttons
    connect(ui->level1Button, &QPushButton::clicked, this, &MainWindow::onLevelButtonClicked);
    connect(ui->level2Button, &QPushButton::clicked, this, &MainWindow::onLevelButtonClicked);
    connect(ui->level3Button, &QPushButton::clicked, this, &MainWindow::onLevelButtonClicked);
    connect(ui->level4Button, &QPushButton::clicked, this, &MainWindow::onLevelButtonClicked);

    // Connect slots for the Chemical buttons


    //    ui->popupModal->setVisible(false);
}

void MainWindow::setupModel(model& model){
    connect(this, &MainWindow::createElement, &model, &model::onCreateElement);
    connect(this, &MainWindow::clearScene, &model, &model::onClearScene);
    connect(this, &MainWindow::updateLevel, &model, &model::onUpdateLevel);

}


void MainWindow::showGameScreen()
{
    // Switch to the game screen
    ui->stackedWidget->setCurrentIndex(1);
    emit updateLevel(0);
    // Set start to level 1
    //ui->leftNavBar->setCurrentIndex(0);
}


// Reset game slot
void MainWindow::restartGame()
{
    // Clear the display labels in each level tab

    // Switch to the start screen
    ui->stackedWidget->setCurrentIndex(0);
    emit clearScene();
}


void MainWindow::showStatsPopup()
{
    ui->popupModal->setVisible(true);

    // Connect the closeButton's clicked signal to a slot
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);
}


void MainWindow::showHintsPopup()
{
    ui->popupModal->setVisible(true);

    // Connect the closeButton's clicked signal to a slot
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);
}


void MainWindow::showHowToPlayPopup()
{
    ui->popupModal->setVisible(true);

    // Connect the closeButton's clicked signal to a slot
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);
}


// Function to handle the closeButton click
void MainWindow::onCloseButtonClicked() {

    if (ui->popupModal->isVisible()) {
        ui->popupModal->setVisible(false);
    }
}


void MainWindow::onClearButtonClicked()
{
    //TODO
    emit clearScene();
}


void MainWindow::onLevelButtonClicked()
{
    //TODO

    // Check which level button was clicked
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

    if (!clickedButton)
    {
        // Handle the case where the sender is not a QPushButton
        return;
    }

    // Change the background image based on the level button clicked
    if (clickedButton == ui->level1Button)
    {
        // Set the background image for level 1
        ui->gameScreen->setStyleSheet("background-image: url(:/UI/UI/GameScreenBackground.png);");
        emit updateLevel(0);
    } else if (clickedButton == ui->level2Button)
    {
        // Set the background image for level 2
        ui->gameScreen->setStyleSheet("background-image: url(:/UI/UI/Game Screen-LEVEL2.png);");
        emit updateLevel(1);
    } else if (clickedButton == ui->level3Button)
    {
        // Set the background image for level 3
        ui->gameScreen->setStyleSheet("background-image: url(:/UI/UI/Game Screen-LEVEL3.png);");
        emit updateLevel(2);
    } else if (clickedButton == ui->level4Button)
    {
        // Set the background image for level 4
        emit updateLevel(3);
        ui->gameScreen->setStyleSheet("background-image: url(:/UI/UI/Game Screen-LEVEL4.png);");
    }

}


void MainWindow::onChemicalButtonClicked()
{
    //TODO
//    emit createElement(0);
}



