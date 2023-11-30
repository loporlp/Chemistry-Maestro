#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QGroupBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up the start screen and game screen
    setupStartScreen();
    setupGameScreen();
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

    //    // Connect slots for the Level buttons
    //    connect(ui->level1Button, &QPushButton::clicked, this, &MainWindow::onLevelButtonClicked);
    //    connect(ui->level2Button, &QPushButton::clicked, this, &MainWindow::onLevelButtonClicked);
    //    connect(ui->level3Button, &QPushButton::clicked, this, &MainWindow::onLevelButtonClicked);
    //    connect(ui->level4Button, &QPushButton::clicked, this, &MainWindow::onLevelButtonClicked);

    // Connect slots for the Chemical buttons


    //    ui->popupModal->setVisible(false);
}


void MainWindow::showGameScreen()
{
    // Switch to the game screen
    ui->stackedWidget->setCurrentIndex(1);

    // Set start to level 1
    //ui->leftNavBar->setCurrentIndex(0);
}


// Reset game slot
void MainWindow::restartGame()
{
    // Clear the display labels in each level tab

    // Switch to the start screen
    ui->stackedWidget->setCurrentIndex(0);
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
}


void MainWindow::onLevelButtonClicked()
{
    //TODO

}


void MainWindow::onChemicalButtonClicked()
{
    //TODO

}



