#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showGameScreen();
    void resetGame();
    void showStatsPopup();
    void showHintsPopup();

    void onChemicalButtonClicked(int number);
    void onClearButtonClicked();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;

    void setupStartScreen();
    void setupGameScreen();

    // Left nav bar tab widget pointer
    QTabWidget *leftNavBar;
};
#endif // MAINWINDOW_H
