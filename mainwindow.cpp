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
    // Create start screen widget
    //QWidget *startScreen = new QWidget(this);
    //QPushButton *startButton = new QPushButton("Start", startScreen);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::showGameScreen);

    // Set layout for start screen
   // QVBoxLayout *startLayout = new QVBoxLayout(startScreen);
   // startLayout->addWidget(startButton);
   // startScreen->setLayout(startLayout);

    // Add start screen to the stacked widget
    // ui->stackedWidget->addWidget(ui->startScreen);
}


void MainWindow::setupGameScreen()
{
    // Create game screen widget
    //QWidget *gameScreen = new QWidget(this);
    //QPushButton *resetButton = new QPushButton("Reset", gameScreen);
    connect(ui->restartButton, &QPushButton::clicked, this, &MainWindow::resetGame);

    // Connect the button's signal to a custom slot for showing the tooltip
    if(ui->hydrogenButton->hasFocus())
    {
        ui->hydrogenButton->toolTip();
    }

//    // Create left-side navigation bar (QTabWidget)
//    //leftNavBar = new QTabWidget(gameScreen);
//    leftNavBar->setTabPosition(QTabWidget::West);
//    for (int i = 1; i <= 5; ++i) {
//        QWidget *levelWidget = new QWidget(leftNavBar);

//        // Create a layout for the level tab widget
//        QVBoxLayout *levelLayout = new QVBoxLayout(levelWidget);

//        // Create a QLabel for displaying the level description
//        QLabel *levelDescriptionLabel = new QLabel(QString("Description for Level %1").arg(i));
//        levelLayout->addWidget(levelDescriptionLabel);

//        // Create a QLabel for displaying the chemical button numbers
//        QLabel *displayLabel = new QLabel(levelWidget);
//        displayLabel->setObjectName("displayLabel"); // Set object name for finding later
//        levelLayout->addWidget(displayLabel);

//        // Set the layout for the level tab widget
//        levelWidget->setLayout(levelLayout);

//        leftNavBar->addTab(levelWidget, QString("Level %1").arg(i));
//    }

//    // Create right-side navigation bar (QVBoxLayout)
//    QVBoxLayout *rightNavBarLayout = new QVBoxLayout();

//    // Create a 3x5 matrix of chemical buttons
//    QGridLayout *chemicalButtonsLayout = new QGridLayout();
//    int counter = 1; // Counter for numbering the chemical buttons
//    for (int row = 0; row < 5; ++row) {
//        for (int col = 0; col < 3; ++col) {

//            QPushButton *chemicalButton = new QPushButton(QString("Chemical %1").arg(counter), gameScreen);
//            // Connect a slot for the chemical button clicked
//            connect(chemicalButton, &QPushButton::clicked, this, [this, counter]() {
//                onChemicalButtonClicked(counter);
//            });
//            chemicalButtonsLayout->addWidget(chemicalButton, row, col);
//            ++counter;
//        }
//    }


//    // Create buttons along the bottom of the right-side nav bar
//    QPushButton *clearButton = new QPushButton("Clear", gameScreen);
//    QPushButton *statsButton = new QPushButton("Stats", gameScreen);
//    QPushButton *hintsButton = new QPushButton("Hints", gameScreen);

//    // Connect slots for the 'Stats' and 'Hints' buttons
    connect(ui->statsButton, &QPushButton::clicked, this, &MainWindow::showStatsPopup);
    connect(ui->hintButton, &QPushButton::clicked, this, &MainWindow::showHintsPopup);
    connect(ui->howToPlayButton, &QPushButton::clicked, this, &MainWindow::showHowToPlayPopup);

//    // Connect slot for the clear button
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);

    // Connect slot for the reset button
//    connect(ui->restartButton, &QPushButton::clicked, this, &MainWindow::resetGame);

//    // Add buttons to the right-side nav bar layout
//    rightNavBarLayout->addLayout(chemicalButtonsLayout);
//    rightNavBarLayout->addWidget(resetButton);
//    rightNavBarLayout->addWidget(clearButton);
//    rightNavBarLayout->addWidget(statsButton);
//    rightNavBarLayout->addWidget(hintsButton);

//    // Create a container widget for the right-side nav bar layout
//    QWidget *rightNavBarContainer = new QWidget(gameScreen);
//    rightNavBarContainer->setLayout(rightNavBarLayout);

//    // Create the main layout for the game screen
//    QHBoxLayout *gameLayout = new QHBoxLayout(gameScreen);
//    gameLayout->addWidget(leftNavBar);
//    gameLayout->addWidget(rightNavBarContainer);
//    gameScreen->setLayout(gameLayout);

//    // Connect the tabChanged signal to update the level description
//    connect(leftNavBar, &QTabWidget::currentChanged, this, [this](int index) {
//        // Retrieve the level description label from the current tab widget
//        QWidget *currentTabWidget = leftNavBar->widget(index);
//        QLabel *levelDescriptionLabel = currentTabWidget->findChild<QLabel*>("levelDescriptionLabel");

//        // Update the level description based on the selected tab index
//        if (levelDescriptionLabel) {
//            levelDescriptionLabel->setText(QString("Description for Level %1").arg(index + 1));
//        }
//    });

//    // Add game screen to the stacked widget
//    ui->stackedWidget->addWidget(gameScreen);

    ui->popupModal->setVisible(false);
}


void MainWindow::showGameScreen()
{
    // Switch to the game screen
    ui->stackedWidget->setCurrentIndex(1);
    //ui->leftNavBar->setCurrentIndex(0);
}


// Reset game slot
void MainWindow::resetGame()
{
//    // Clear the display labels in each level tab
//    for (int i = 0; i < leftNavBar->count(); ++i) {
//        QWidget *levelTab = leftNavBar->widget(i);
//        QLabel *displayLabel = levelTab->findChild<QLabel*>("displayLabel");
//        if (displayLabel) {
//            displayLabel->clear();
//        }
//    }

    // Switch to the start screen
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::showStatsPopup()
{
    ui->popupModal->setVisible(true);

    // Connect the closeButton's clicked signal to a slot
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);

//    connect(ui->closeButton, &QPushButton::clicked, statsDialog, &QDialog::close);

//    // Create a QDialog for the stats popup
//    QDialog *statsDialog = new QDialog(this);
//    statsDialog->setWindowTitle("Stats");

//    // Set up the layout for the stats popup
//    QVBoxLayout *layout = new QVBoxLayout(statsDialog);
//    layout->addWidget(new QLabel("Statistics go here."));

//    // Add a close button to the popup
//    QPushButton *closeButton = new QPushButton("Close");
//    connect(closeButton, &QPushButton::clicked, statsDialog, &QDialog::close);
//    layout->addWidget(closeButton);

//    // Set the layout for the stats popup
//    statsDialog->setLayout(layout);

//    // Show the stats popup
//    statsDialog->exec();
}


void MainWindow::showHintsPopup()
{
    ui->popupModal->setVisible(true);

    // Connect the closeButton's clicked signal to a slot
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);

    // Create a QDialog for the hints popup
    //QDialog *hintsDialog = new QDialog(this);
    //hintsDialog->setStyleSheet();

    // Set up the layout for the hints popup
    //QVBoxLayout *layout = new QVBoxLayout(hintsDialog);
    //layout->addWidget(new QLabel("Hints go here."));

    // Add a close button to the popup
    //QPushButton *closeButton = new QPushButton("Close");
    //connect(ui->closeButton, &QPushButton::clicked, hintsDialog, &QDialog::close);
    //layout->addWidget(closeButton);

    // Set the layout for the hints popup
    //hintsDialog->setLayout(layout);

    // Show the hints popup
    //hintsDialog->exec();
}

void MainWindow::showHowToPlayPopup()
{
    ui->popupModal->setVisible(true);

    // Connect the closeButton's clicked signal to a slot
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);

    // Create a QDialog for the hints popup
    //QDialog *hintsDialog = new QDialog(this);
    //hintsDialog->setStyleSheet();

    // Set up the layout for the hints popup
    //QVBoxLayout *layout = new QVBoxLayout(hintsDialog);
    //layout->addWidget(new QLabel("Hints go here."));

    // Add a close button to the popup
    //QPushButton *closeButton = new QPushButton("Close");
    //connect(ui->closeButton, &QPushButton::clicked, hintsDialog, &QDialog::close);
    //layout->addWidget(closeButton);

    // Set the layout for the hints popup
    //hintsDialog->setLayout(layout);

    // Show the hints popup
    //hintsDialog->exec();
}

// Function to handle the closeButton click
void MainWindow::onCloseButtonClicked() {

    if (ui->popupModal->isVisible()) {
        ui->popupModal->setVisible(false);
    }
}


void MainWindow::onChemicalButtonClicked(int number)
{
//    // Get the current index of the left navigation bar
//    int currentIndex = leftNavBar->currentIndex();

//    // Get the level tab widget corresponding to the current index
//    QWidget *currentTabWidget = leftNavBar->widget(currentIndex);

//    // Find the QLabel for displaying the chemical button numbers
//    QLabel *displayLabel = currentTabWidget->findChild<QLabel*>("displayLabel");

//    // If the QLabel is found, append the number to the display
//    if (displayLabel) {
//        QString currentText = displayLabel->text();
//        if (!currentText.isEmpty()) {
//            currentText += ", ";
//        }
//        displayLabel->setText(currentText + QString::number(number));
//    }
}


void MainWindow::onClearButtonClicked()
{
//    // Get the current index of the left navigation bar
//    int currentIndex = leftNavBar->currentIndex();

//    // Get the level tab widget corresponding to the current index
//    QWidget *currentTabWidget = leftNavBar->widget(currentIndex);

//    // Find the QLabel for displaying the chemical button numbers
//    QLabel *displayLabel = currentTabWidget->findChild<QLabel*>("displayLabel");

//    // If the QLabel is found, clear the display
//    if (displayLabel) {
//        displayLabel->clear();
//    }
}
