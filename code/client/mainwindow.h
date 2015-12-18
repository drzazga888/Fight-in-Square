#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QHostAddress>
#include "config.h"
#include "canvas.h"
#include "Game.h"
#include "NetworkManager.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

public slots:
    void onGameStatusChanged(Game::STATUS gameStatus);

private slots:
    void on_connectButton_clicked();
    void on_helpButton_clicked();
    void on_exitButton_clicked();

private:
    void keyPressEvent(QKeyEvent *e);
    Ui::MainWindow *ui;
    Game game;
    Canvas canvas;
    NetworkManager networkManager;

};

#endif // MAINWINDOW_H
