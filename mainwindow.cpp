#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QGroupBox>
#include <QTimer>
#include <QDebug>
#include <vector>


MainWindow::MainWindow(model& model, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    world(b2Vec2(0.0f, -10.0f))
{
    ui->setupUi(this);
    qApp->setWindowIcon(QIcon(":/UI/UI/oxygen.png"));

    currentLevel = 1;
    bodiesLocked = false;

    // Set up the start screen and game screen
    setupStartScreen();
    setupGameScreen();

    setupModel(model);

    // define ground / wall bodies
    b2BodyDef groundBodyDef;
    b2BodyDef leftWallDef;
    b2BodyDef rightWallDef;
    groundBodyDef.position.Set(0.0f, -15.03f);
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
    connect(ui->hydrogenButton, &QPushButton::clicked, this, [this]{ addBody(":/UI/UI/hydrogen.png", 1.0);
        emit createElement(element::H);
    });
    connect(ui->heliumButton, &QPushButton::clicked, this, [this]{ addBody(":/UI/UI/helium.png", 1.0);
        emit createElement(element::He);
    });
    connect(ui->carbonButton, &QPushButton::clicked, this, [this]{ addBody(":/UI/UI/carbon.png", 1.0);
        emit createElement(element::C);
    });
    connect(ui->nitrogenButton, &QPushButton::clicked, this, [this]{ addBody(":/UI/UI/nitrogen.png", 1.0);
        emit createElement(element::N);
    });
    connect(ui->oxygenButton, &QPushButton::clicked, this, [this]{ addBody(":/UI/UI/oxygen.png", 1.0);
        emit createElement(element::O);
    });
    connect(ui->sodiumButton, &QPushButton::clicked, this, [this]{ addBody(":/UI/UI/sodium.png", 1.0);
        emit createElement(element::Na);
    });
    connect(ui->aluminiumButton, &QPushButton::clicked, this, [this]{ addBody(":/UI/UI/aluminum.png", 1.0);
        emit createElement(element::Al);
    });
    connect(ui->potassiumButton, &QPushButton::clicked, this, [this]{ addBody(":/UI/UI/potassium.png", 1.0);
        emit createElement(element::K);
    });
    connect(ui->calciumButton, &QPushButton::clicked, this, [this]{ addBody(":/UI/UI/calcium.png", 1.0);
        emit createElement(element::Ca);
    });
    connect(ui->ironButton, &QPushButton::clicked, this, [this]{ addBody(":/UI/UI/iron.png", 1.0);
        emit createElement(element::Fe);
    });
    connect(ui->nickelButton, &QPushButton::clicked, this, [this]{ addBody(":/UI/UI/nickel.png", 1.0);
        emit createElement(element::Ni);
    });
    connect(ui->copperButton, &QPushButton::clicked, this, [this]{ addBody(":/UI/UI/copper.png", 1.0);
        emit createElement(element::Cu);
    });
    connect(ui->zincButton, &QPushButton::clicked, this, [this]{ addBody(":/UI/UI/zinc.png", 1.0);
        emit createElement(element::Zn);
    });
    connect(ui->silverButton, &QPushButton::clicked, this, [this]{ addBody(":/UI/UI/silver.png", 1.0);
        emit createElement(element::Ag);
    });
    connect(ui->tinButton, &QPushButton::clicked, this, [this]{ addBody(":/UI/UI/DavidJohnsTin.png", 1.0);
        emit createElement(element::Sn);
    });

    // Test run
    connect(ui->ironButton, &QPushButton::clicked, this, &MainWindow::onChemicalButtonClicked);

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

void MainWindow::addBody(QString imgPath, float32 scale)
{
    if(bodiesLocked) { return; }

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(1.75f, 4.0f);
    b2Body *body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox((0.33f * scale), (0.33f * scale));

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    fixtureDef.restitution = 0.7f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    if(scale > 1) {
        scale *= 0.8;
    }

    //bodies->push_back(body);
    QLabel *newLabel = new QLabel(this);
    QImage *image = new QImage();
    image->load(
        imgPath);
    newLabel->setPixmap(QPixmap::fromImage(image->scaled((75 * (scale)), (75 * (scale)), Qt::KeepAspectRatio)));
    newLabel->show();
    newLabel->setFixedHeight((int32)(75 * (scale)));
    newLabel->setFixedWidth((int32)(75 * (scale)));

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

//    ui->level2Button->setDisabled(true);
//    ui->level3Button->setDisabled(true);
//    ui->level4Button->setDisabled(true);

//    ui->level2Button->setIcon(QIcon(":/UI/UI/lockIcon.png"));
//    ui->level3Button->setIcon(QIcon(":/UI/UI/lockIcon.png"));
//    ui->level4Button->setIcon(QIcon(":/UI/UI/lockIcon.png"));

    // Connect slots for the Chemical buttons

    //    ui->popupModal->setVisible(false);
}

void MainWindow::setupModel(model& model){
    connect(this, &MainWindow::createElement, &model, &model::onCreateElement);
    connect(this, &MainWindow::clearScene, &model, &model::onClearScene);
    connect(this, &MainWindow::updateLevel, &model, &model::onUpdateLevel);
    connect(&model, &model::successfulCombination, this, &MainWindow::onSuccessfulCombination);
}


void MainWindow::showGameScreen()
{
    // Switch to the game screen
    ui->stackedWidget->setCurrentIndex(1);

    showLevelInstructionsPopup(1);
    ui->gameScreen->setStyleSheet("background-image: url(:/UI/UI/GameScreenBackground.png);");

    // model signals.
    emit clearScene();
    emit updateLevel(0);
    // Set start to level 1
    //ui->leftNavBar->setCurrentIndex(0);
}


// Reset game slot
void MainWindow::restartGame()
{
    // Clear the display labels in each level tab
    //    resetLevelData(currentLevel);
    resetLevelData(1);

    // Switch to the start screen
    ui->stackedWidget->setCurrentIndex(0);
    emit clearScene();
}


void MainWindow::showStatsPopup()
{
    ui->popupModal->setVisible(true);
    setLabelVisible(false);

    //ui->popupModal->setStyleSheet("background-image: url(:/UI/UI/Level 1 Score Popup.png);");

    // Connect the closeButton's clicked signal to a slot
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);
}


void MainWindow::showHintsPopup()
{
    ui->popupModal->setVisible(true);
    setLabelVisible(false);

    switch(currentLevel)
    {
    case 1:
        ui->popupModal->setStyleSheet("background-image: url(:/UI/UI/Level 1 Hint.png);");
        break;
    case 2:
        ui->popupModal->setStyleSheet("background-image: url(:/UI/UI/Level 2 Hint.png);");
        break;
    case 3:
        ui->popupModal->setStyleSheet("background-image: url(:/UI/UI/Level 3 Hint.png);");
        break;
    case 4:
        ui->popupModal->setStyleSheet("background-image: url(:/UI/UI/Level 4 Hint.png);");
        break;
    }

    // Connect the closeButton's clicked signal to a slot
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);
}


void MainWindow::showHowToPlayPopup()
{
    ui->popupModal->setVisible(true);
    setLabelVisible(false);

    ui->popupModal->setStyleSheet("background-image: url(:/UI/UI/How to Play Popup.png);");

    // Connect the closeButton's clicked signal to a slot
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);
}


// Function to handle the closeButton click
void MainWindow::onCloseButtonClicked() {
    setLabelVisible(true);
    if (ui->popupModal->isVisible()) {
        ui->popupModal->setVisible(false);
    }
}


void MainWindow::onClearButtonClicked()
{
    emit clearScene();
    resetLevelData();
}

void MainWindow::resetLevelData()
{
    resetLevelData(currentLevel);
}

void MainWindow::resetLevelData(int32 newLevelValue)
{
    bodiesLocked = false;
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
        //ui->LevelInstructionModal->setStyleSheet("background-image: url(:/UI/UI/Level 1 Instructions.png);");
        showLevelInstructionsPopup(1);

        // remove the chemicals added to the world, change the current level value
        resetLevelData(1);
        // model signals.
        emit clearScene();
        emit updateLevel(0);
    } else if (clickedButton == ui->level2Button && currentLevel != 2)
    {
        // Set the background image for level 2
        ui->gameScreen->setStyleSheet("background-image: url(:/UI/UI/Game Screen-LEVEL2.png);");
        //ui->LevelInstructionModal->setStyleSheet("background-image: url(:/UI/UI/Level 2 Instructions.png);");
        showLevelInstructionsPopup(2);

        // remove the chemicals added to the world, change the current level value
        resetLevelData(2);
        // model signals.
        emit clearScene();
        emit updateLevel(1);
    } else if (clickedButton == ui->level3Button && currentLevel != 3)
    {
        // Set the background image for level 3
        ui->gameScreen->setStyleSheet("background-image: url(:/UI/UI/Game Screen-LEVEL3.png);");
        //ui->LevelInstructionModal->setStyleSheet("background-image: url(:/UI/UI/Level 3 Instructions.png);");
        showLevelInstructionsPopup(3);

        // remove the chemicals added to the world, change the current level value
        resetLevelData(3);
        // model signals.
        emit clearScene();
        emit updateLevel(2);
    } else if (clickedButton == ui->level4Button && currentLevel != 4)
    {
        // Set the background image for level 4
        ui->gameScreen->setStyleSheet("background-image: url(:/UI/UI/Game Screen-LEVEL4.png);");
        //ui->LevelInstructionModal->setStyleSheet("background-image: url(:/UI/UI/Level 4 Instructions.png);");
        showLevelInstructionsPopup(4);

        // remove the chemicals added to the world, change the current level value
        resetLevelData(4);
        // model signals.
        emit clearScene();
        emit updateLevel(3);

    }

}

void MainWindow::showLevelInstructionsPopup(int selectedLevel)
{

    // Set the background image based on the current level
    switch(selectedLevel)
    {
    case 1:
        ui->LevelInstructionModal->setStyleSheet("background-image: url(:/UI/UI/Level 1 Instructions.png);");
        break;

    case 2:
        ui->LevelInstructionModal->setStyleSheet("background-image: url(:/UI/UI/Level 2 Instructions.png);");
        break;

    case 3:
        ui->LevelInstructionModal->setStyleSheet("background-image: url(:/UI/UI/Level 3 Instructions.png);");
        break;

    case 4:
        ui->LevelInstructionModal->setStyleSheet("background-image: url(:/UI/UI/Level 4 Instructions.png);");
        break;
    }

    // Make the modal visible and hide other elements
    ui->LevelInstructionModal->setVisible(true);
    ui->howToPlayButton->setDisabled(true);
    //setLabelVisible(false);

    // Connect the closeButton's clicked signal to a slot
    connect(ui->closeLevelInstructionButton, &QPushButton::clicked, this, &MainWindow::onCloseLevelInstructionButtonClicked);
}


void MainWindow::onCloseLevelInstructionButtonClicked()
{
    // Close the modal when the close button is clicked
    ui->LevelInstructionModal->setVisible(false);
    ui->howToPlayButton->setDisabled(false);

    // Optionally, show other elements again if needed
    //setLabelVisible(true);
}


void MainWindow::onChemicalButtonClicked()
{
    // Test run
}

void MainWindow::setLabelVisible(bool visible){
    for(auto label : bodyDisplays)
    {
        label->setVisible(visible);
    }
}

void MainWindow::addChemical(QString imgPath)
{
    QTimer::singleShot(1000, this, [this] () {
        for(auto body : bodies)
        {
            body->ApplyAngularImpulse(400.0f, true);
        }
    });
    QTimer::singleShot(3500, this, SLOT(resetLevelData()));
    QTimer::singleShot(3510, this, [this, imgPath] () {
        addBody(imgPath, 1.75);
        bodiesLocked = true;
    });

}


void MainWindow::onSuccessfulCombination(molecule newMolecule){
    // Test run
    // clear elements on screen, instantiate molecule physics object, unlock next level(?)
    qDebug() << "Made water!";
    qDebug() << &newMolecule;


    switch(currentLevel)
    {
    case 1:
        addChemical(":/UI/UI/water.png");
        //unlock level 2 TODO
        //ui->level2Button->setDisabled(false);
        //ui->popupModal->setStyleSheet("background-image: url(:/UI/UI/Level 1 Score Popup.png);");
        //showStatsPopup();

        break;
    case 2:
        addChemical(":/UI/UI/water.png");
        //unlock level 3 TODO
        //ui->level3Button->setDisabled(false);

        break;
    case 3:
        addChemical(":/UI/UI/water.png");
        //unlock level 4 TODO
        //ui->level4Button->setDisabled(false);

        break;
    case 4:
        addChemical(":/UI/UI/water.png");
        //Display game over/final stats screen TODO
        break;
    }

    emit clearScene();
}



