#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QGroupBox>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include<QTimer>
#include <QDebug>
#include<vector>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    world(b2Vec2(0.0f, -10.0f))
{
    ui->setupUi(this);

    // temporary magic number - change later.
    currentLevel = 1;

    // Set up the start screen and game screen
    setupStartScreen();
    setupGameScreen();

    // define ground / wall bodies
    b2BodyDef groundBodyDef;
    b2BodyDef leftWallDef;
    b2BodyDef rightWallDef;
    groundBodyDef.position.Set(0.0f, -15.0f);
    leftWallDef.position.Set(-.35f, -10.0f);
    rightWallDef.position.Set(3.7f, -10.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body *groundBody = world.CreateBody(&groundBodyDef);
    b2Body *leftWallBody = world.CreateBody(&leftWallDef);
    b2Body *rightWallBody = world.CreateBody(&rightWallDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;
    b2PolygonShape leftWallBox;
    b2PolygonShape rightWallBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 10.0);

    leftWallBox.SetAsBox(1.0f, 55.0f);
    rightWallBox.SetAsBox(1.0f, 55.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);
    leftWallBody->CreateFixture(&leftWallBox, 0.0f);
    rightWallBody->CreateFixture(&rightWallBox, 0.0f);

    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    QTimer *timer = new QTimer(this);

    QImage *image = new QImage();
    image->load(
          ":/UI/UI/david.png");

    connect(timer,
            &QTimer::timeout,
            this,
            [this, timeStep, velocityIterations, positionIterations]() {
                updateWorld(timeStep, velocityIterations, positionIterations);
            });
    //connect(this, &MainWindow::positionChanged, ui->frame, );
    connect(ui->ironButton, &QPushButton::clicked, this, &MainWindow::addBody);

    timer->start(10);
    qDebug() << this->size().height() << "height";
    qDebug() << this->size().width() << "width";
}

void MainWindow::updateWorld(float32 timeStep, int32 velocityIterations, int32 positionIterations)
{
    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    world.Step(timeStep, velocityIterations, positionIterations);

    int i = 0;
    for (auto body : bodies) {
        auto position = body->GetPosition();
        bodyDisplays.at(i)->move((position.x + 2) * 100, (-1 * (position.y - 1) * 100) - 126);
        //bodies = bodies->GetNext();
        i++;
    }
}

void MainWindow::addBody()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(1.75f, 4.0f);
    b2Body *body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.33f, 0.33f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    fixtureDef.restitution = 0.8f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    //bodies->push_back(body);
    QLabel *newLabel = new QLabel(this);
    QImage *image = new QImage();
    image->load(
          ":/UI/UI/david.png");
    newLabel->setPixmap(QPixmap::fromImage(image->scaled(100, 100, Qt::KeepAspectRatio)));
    newLabel->show();
    newLabel->setFixedHeight(75);
    newLabel->setFixedWidth(75);

    bodyDisplays.push_back(newLabel);
    bodies.push_back(body);
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
    resetLevelData(currentLevel);

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
    resetLevelData(currentLevel);
}

void MainWindow::resetLevelData(int32 newLevelValue)
{
    currentLevel = newLevelValue;

    for(b2Body *body : bodies) {
        world.DestroyBody(body);
    }

    for(auto label : bodyDisplays) {
        delete label;
    }

    bodies.clear();
    bodyDisplays.clear();
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
    if (clickedButton == ui->level1Button && currentLevel != 1)
    {
        // Set the background image for level 1
        ui->gameScreen->setStyleSheet("background-image: url(:/UI/UI/GameScreenBackground.png);");

        // remove the chemicals added to the world, change the current level value
        resetLevelData(1);
    } else if (clickedButton == ui->level2Button && currentLevel != 2)
    {
        // Set the background image for level 2
        ui->gameScreen->setStyleSheet("background-image: url(:/UI/UI/Game Screen-LEVEL2.png);");

        // remove the chemicals added to the world, change the current level value
        resetLevelData(2);
    } else if (clickedButton == ui->level3Button && currentLevel != 3)
    {
        // Set the background image for level 3
        ui->gameScreen->setStyleSheet("background-image: url(:/UI/UI/Game Screen-LEVEL3.png);");

        // remove the chemicals added to the world, change the current level value
        resetLevelData(3);
    } else if (clickedButton == ui->level4Button && currentLevel != 4)
    {
        // Set the background image for level 4
        ui->gameScreen->setStyleSheet("background-image: url(:/UI/UI/Game Screen-LEVEL4.png);");

        // remove the chemicals added to the world, change the current level value
        resetLevelData(4);
    }

}


void MainWindow::onChemicalButtonClicked()
{
    //TODO

}



