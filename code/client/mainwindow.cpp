#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent), ui(new Ui::MainWindow), game(), canvas(&game), networkManager(&game)
{
    ui->setupUi(this);
    canvas.setParent(ui->canvasBack);
    //ui->stackedWidget->setCurrentWidget(ui->menu);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT + 22);
    ui->top->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->top->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    connect(&game, SIGNAL(gameStatusChanged(Game::STATUS)), this, SLOT(onGameStatusChanged(Game::STATUS)));
    connect(&game, SIGNAL(modelActualized()), this, SLOT(onModelActualized()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Space && e->isAutoRepeat())
        return;
    game.handleKeyPress(e->key());
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    game.handleKeyRelease(e->key());
}

void MainWindow::onGameStatusChanged(Game::STATUS gameStatus)
{
    switch (gameStatus)
    {
    case Game::NO_PLAYING:
        //canvas.releaseKeyboard();
        ui->connectButton->setText("Połącz");
        ui->stackedWidget->setCurrentWidget(ui->menu);
        ui->statusbar->showMessage("");
        break;
    case Game::CONNECTING:
        ui->connectButton->setText("Rozłącz");
        ui->statusbar->showMessage("Łączenie z serwerem...");
        break;
    case Game::SENDING_HELLO:
        ui->statusbar->showMessage("Wysyłanie komunikatu powitalnego...");
        break;
    case Game::PLAYING:
        //canvas.grabKeyboard();
        ui->stackedWidget->setCurrentWidget(ui->game);
        ui->exitGameButton->setEnabled(true);
        ui->statusbar->showMessage("Połączono!");
        updated = false;
        break;
    case Game::SENDING_GOODBYE:
        ui->exitGameButton->setEnabled(true);
        ui->statusbar->showMessage("Wysyłanie komunikatu pożegnalnego...");
        break;
    case Game::DISCONNECTING:
        ui->statusbar->showMessage("Rozłączanie...");
        break;
    }
}

void MainWindow::onModelActualized()
{
    game.gameTime = game.gameTime.addMSecs(SERVER_SEND_INTERVAL);
    Player &player = game.model2.players[game.player.id];
    if (!updated)
    {
        QColor color = player.group == Player::RED_GROUP ? QColor(255, 0, 0) : QColor(0, 100, 255);
        ui->playerName->setText(QString("<font color='%1'>%2</font>").arg(color.name(), game.playerName));
        updated = true;
    }
    ui->healthBar->setValue(player.health);
    ui->powerBar->setValue(player.power);
    ui->pointsLabel->setText(QString("Punkty: %1").arg(player.points));
    ui->timeLabel->setText(QString("Czas: %1").arg(game.gameTime.toString("mm:ss")));
    QMap<int, Player> playerPoints;
    QMapIterator<int, Player> i(game.model2.players);
    while (i.hasNext())
    {
        i.next();
        playerPoints.insert(i.value().points, i.value());
    }
    i = QMapIterator<int, Player>(playerPoints);
    for (int j = 0; j < ui->top->rowCount(); ++j)
    {
        QTableWidgetItem *name, *points;
        if (i.hasNext())
        {
            i.next();
            name = new QTableWidgetItem(i.value().name.data());
            points = new QTableWidgetItem(QString::number(i.value().points));
        }
        else
        {
            name = new QTableWidgetItem("---");
            points = new QTableWidgetItem("---");
        }
        ui->top->setItem(j, 0, name);
        ui->top->setItem(j, 1, points);
    }
}

void MainWindow::on_connectButton_clicked()
{
    switch (game.status)
    {
    case Game::NO_PLAYING:
        if (ui->playerNameEdit->text() == "")
            ui->statusbar->showMessage("Proszę podać nazwę gracza.");
        else if (ui->serverIpEdit->text() == "")
            ui->statusbar->showMessage("Proszę podać adres IP.");
        else if (ui->serverPortEdit->text() == "" || ui->serverPortEdit->text().toInt() == 0)
            ui->statusbar->showMessage("Proszę podać poprawny port.");
        else
            networkManager.connectToHost(QHostAddress(ui->serverIpEdit->text()), ui->serverPortEdit->text().toInt(), ui->playerNameEdit->text());
        break;
    default:
        networkManager.disconnectFromHost();
        break;
    }
}

void MainWindow::on_helpButton_clicked()
{
    ui->statusbar->showMessage("Brak dołączonej pomocy.");
}

void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}

void MainWindow::on_exitGameButton_clicked()
{
    networkManager.disconnectFromHost();
}
