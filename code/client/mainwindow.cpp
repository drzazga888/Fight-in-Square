#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent), ui(new Ui::MainWindow), game(), canvas(&game), networkManager(&game)
{
    ui->setupUi(this);
    canvas.setParent(ui->canvasBack);
    //ui->stackedWidget->setCurrentWidget(ui->menu);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT + 22);
    connect(&game, SIGNAL(gameStatusChanged(Game::STATUS)), this, SLOT(onGameStatusChanged(Game::STATUS)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    game.handleKeyboard(e->key());
}

void MainWindow::onGameStatusChanged(Game::STATUS gameStatus)
{
    switch (gameStatus){
        case Game::MENU:
            ui->stackedWidget->setCurrentWidget(ui->menu);
            break;
        case Game::CONNECTING:
            ui->connectButton->setEnabled(false);
            ui->connectButton->setText("Łączenie...");
            ui->statusbar->showMessage("Łączenie z serwerem...");
            break;
        case Game::BEFORE_PLAYING:
            ui->statusbar->showMessage("Wymienianie informacji przed grą...");
            break;
        case Game::PLAYING:
            ui->statusbar->showMessage("Połączono! Witaj w grze!");
            ui->stackedWidget->setCurrentWidget(ui->game);
            break;
    }
}

void MainWindow::on_connectButton_clicked()
{
    if (ui->playerNameEdit->text() == "")
        ui->statusbar->showMessage("Proszę podać nazwę gracza.");
    else if (ui->serverIpEdit->text() == "")
        ui->statusbar->showMessage("Proszę podać adres IP.");
    else if (ui->serverPortEdit->text() == "" || ui->serverPortEdit->text().toInt() == 0)
        ui->statusbar->showMessage("Proszę podać poprawny port.");
    else
        networkManager.connectToHost(QHostAddress(ui->serverIpEdit->text()), ui->serverPortEdit->text().toInt(), ui->playerNameEdit->text());
}

void MainWindow::on_helpButton_clicked()
{
    ui->statusbar->showMessage("Brak dołączonej pomocy.");
}

void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}
