#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include<QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void positionChanged(int ax, int ay);

private slots:
    void showGameScreen();
    void restartGame();

    void showStatsPopup();
    void showHintsPopup();
    void showHowToPlayPopup();

    void onCloseButtonClicked();

    void onClearButtonClicked();

    void onLevelButtonClicked();
    void onChemicalButtonClicked();

    void updateWorld(float32 timeStep, int32 velocityIterations, int32 positionIterations);

private:
    Ui::MainWindow *ui;

    b2Body *body;
    b2World world;
    std::vector<QLabel *> bodyDisplays;
    std::vector<b2Body *> bodies;

    void setupStartScreen();
    void setupGameScreen();
    void addBody();
};
#endif // MAINWINDOW_H
