#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent), ui(new Ui::MainWindow), game(), canvas(&game), networkManager(&game)
{
    ui->setupUi(this);
    canvas.setParent(ui->canvasBack);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT + 22);
    ui->top->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->top->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    connect(&game, SIGNAL(gameStatusChanged(Game::STATUS)), this, SLOT(onGameStatusChanged(Game::STATUS)));
    connect(&game, SIGNAL(errorCodeChanged(int)), this, SLOT(onErrorCodeChanged(int)));
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
        ui->connectButton->setText("Połącz");
        if (ui->stackedWidget->currentWidget() != ui->gameOver)
            ui->stackedWidget->setCurrentWidget(ui->menu);
        if (!game.errCode)
            ui->statusbar->showMessage("");
        break;
    case Game::CONNECTING:
        game.errCode = 0;
        ui->connectButton->setText("Rozłącz");
        ui->statusbar->showMessage("Łączenie z serwerem...");
        break;
    case Game::SENDING_HELLO:
        ui->statusbar->showMessage("Wysyłanie komunikatu powitalnego...");
        break;
    case Game::WAITING_FOR_PLAYER:
        ui->statusbar->showMessage("Oczekiwanie na graczy...");
        break;
    case Game::PLAYING:
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
    case Game::GAME_OVER:
        int redPoints = 0, bluePoints = 0;
        foreach (const Player &player, game.model2.players)
        {
            switch (player.group)
            {
            case Player::RED_GROUP:
                redPoints += player.points;
                break;
            case Player::BLUE_GROUP:
                bluePoints += player.points;
                break;
            }
        }
        ui->redPointsLabel->setText(QString("Czerwoni: %1 punktów").arg(redPoints));
        ui->bluePointsLabel->setText(QString("Niebiescy: %1 punktów").arg(bluePoints));
        if (redPoints == bluePoints)
            ui->yourStatusLabel->setText(QStringLiteral("<font color='ff0'>Remis!</font>"));
        else if (
                 ((redPoints > bluePoints) && (game.model2.players[game.player.id].group == Player::RED_GROUP)) ||
                 ((redPoints < bluePoints) && (game.model2.players[game.player.id].group == Player::BLUE_GROUP))
        )
            ui->yourStatusLabel->setText(QStringLiteral("<font color='#6f6'>Wygrana!</font>"));
        else
            ui->yourStatusLabel->setText(QStringLiteral("<font color='#f66'>Przegrana!</font>"));
        fillInTable(ui->topSummary);
        ui->stackedWidget->setCurrentWidget(ui->gameOver);
        break;
    }
}

void MainWindow::onErrorCodeChanged(int errCode)
{
    switch (errCode)
    {
    case USER_NAME_IS_NOT_UNIQUE:
        ui->statusbar->showMessage("Nazwa gracza nie jest unikalna. Wybierz inną nazwę.");
        break;
    case SERVER_IS_FULL:
        ui->statusbar->showMessage(QString("Serwer jest pełny - jest już na nim %1 graczy").arg(MAX_PLAYERS));
        break;
    }
}

bool playerPointsLessThen(const Player &a, const Player &b)
{
    return a.points > b.points;
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
    ui->timeLabel->setText(QString("Czas: %1 / %2").arg(game.gameTime.toString("mm:ss"), game.maxTime.toString("mm:ss")));
    fillInTable(ui->top);
}

void MainWindow::on_connectButton_clicked()
{
    QHostAddress ip;
    bool portValid;
    int port;
    switch (game.status)
    {
    case Game::NO_PLAYING:
        if (!ui->playerNameEdit->text().contains(QRegExp(NAME_REGEX)))
            ui->statusbar->showMessage("Nazwa gracza musi zawierać od 1 do 16 znaków, które są literami, cyframi, '_' lub '.'");
        else if (!ip.setAddress(ui->serverIpEdit->text()))
            ui->statusbar->showMessage("Proszę podać poprawny adres IP");
        else if (port = ui->serverPortEdit->text().toInt(&portValid), !portValid)
            ui->statusbar->showMessage("Proszę podać poprawny port");
        else
            networkManager.connectToHost(ip, port, ui->playerNameEdit->text());
        break;
    default:
        networkManager.disconnectFromHost();
        break;
    }
}

void MainWindow::fillInTable(QTableWidget *table)
{
    QList<Player> playerPoints = game.model2.players.values();
    qStableSort(playerPoints.begin(), playerPoints.end(), playerPointsLessThen);
    QListIterator<Player> i(playerPoints);
    for (int j = 0; j < table->rowCount(); ++j)
    {
        QTableWidgetItem *name, *points;
        if (i.hasNext())
        {
            const Player &player = i.next();
            name = new QTableWidgetItem(player.name.data());
            name->setBackgroundColor(QColor(player.group == Player::RED_GROUP ? "#900" : "#009"));
            points = new QTableWidgetItem(QString::number(player.points));
        }
        else
        {
            name = new QTableWidgetItem("---");
            points = new QTableWidgetItem("---");
        }
        table->setItem(j, 0, name);
        table->setItem(j, 1, points);
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

void MainWindow::on_exitGameOverButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);
}
