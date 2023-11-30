#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(model& model, QWidget *parent = nullptr);
    ~MainWindow();

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


private:
    Ui::MainWindow *ui;

    void setupStartScreen();
    void setupGameScreen();

    void setupModel(model& model);

signals:
    void createElement(int index);
};
#endif // MAINWINDOW_H
