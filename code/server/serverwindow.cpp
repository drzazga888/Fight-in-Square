#include "serverwindow.h"
#include "ui_serverwindow.h"

ServerWindow::ServerWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::ServerWindow), data(), server(data), mapLoaded(false)
{
    ui->setupUi(this);
    connect(&server, SIGNAL(logged(QString)), this, SLOT(server_logged(QString)));
    connect(&server, SIGNAL(playerAdded(Player&)), this, SLOT(server_playerAdded(Player&)));
    connect(&server, SIGNAL(playerRemoved(int)), this, SLOT(server_playerRemoved(int)));
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::on_onOffButton_clicked()
{
    if (server.isWorking && server.switchOff())
    {
        ui->portEdit->setEnabled(true);
        ui->selectMapButton->setEnabled(true);
        ui->onOffButton->setText("Uruchom serwer");
    }
    else
    {
        if (ui->portEdit->text().toInt() == 0)
            ui->statusBar->showMessage("Wprowadzono nieprawidłowy numer portu");
        else if (!mapLoaded)
            ui->statusBar->showMessage("Nie załadowano mapy");
        else if (server.switchOn(ui->portEdit->text().toInt()))
        {
            ui->statusBar->clearMessage();
            ui->portEdit->setEnabled(false);
            ui->selectMapButton->setEnabled(false);
            ui->onOffButton->setText("Rozłącz serwer");
            server.refreshController();
        }
    }
}

void ServerWindow::on_selectMapButton_clicked()
{
    // wybieranie pliku z mapa
    QString fileName = QFileDialog::getOpenFileName(0,"Wczytaj mapę","../server/mapa1.map","Pliki map (*.map)");
    if (!fileName.isEmpty()){
        mapLoaded = true;
        ui->selectedMapLabel->setText(fileName);
    }
    else {
        mapLoaded = false;
        ui->selectedMapLabel->setText(QStringLiteral("(brak)"));
    }
    server.setPathExtendedMap(fileName);
    server.refreshController();
}

void ServerWindow::server_logged(const QString &message)
{
    if (server.isWorking)
    {
        ui->messageBox->textCursor().insertText(message + QString("\n"));
        QScrollBar *v = ui->messageBox->verticalScrollBar();
        v->setValue(v->maximum());
    }
}

void ServerWindow::server_playerAdded(Player &player)
{
    if (server.isWorking)
    {
        QTableWidgetItem *id = new QTableWidgetItem(QString("%1").arg(player.id));
        QTableWidgetItem *group = new QTableWidgetItem(player.group == Player::RED_GROUP ? "Czerwoni" : "Niebiescy");
        QTableWidgetItem *name = new QTableWidgetItem(player.name.data());
        int rows = ui->gamersList->rowCount();
        ui->gamersList->setRowCount(rows + 1);
        ui->gamersList->setItem(rows, 0, id);
        ui->gamersList->setItem(rows, 1, group);
        ui->gamersList->setItem(rows, 2, name);
    }
}

void ServerWindow::server_playerRemoved(int id)
{
    if (server.isWorking)
    {
        QTableWidgetItem *iter;
        for (int i = 0; i < ui->gamersList->rowCount(); ++i)
        {
            iter = ui->gamersList->item(i, 0);
            if (iter->text().toInt() == id)
            {
                ui->gamersList->removeRow(i);
                return;
            }
        }
        qDebug() << "Nie mozna usunac gracza, ktory istnieje, id = " << id;
    }
}

void ServerWindow::closeEvent(QCloseEvent *event)
{
    server.switchOff();
    event->accept();
}
