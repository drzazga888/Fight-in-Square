#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include <QCloseEvent>
#include "Server.h"

namespace Ui {
class ServerWindow;
}

class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();

private slots:
    void on_onOffButton_clicked();
    void server_logged(const QString &message);
    void server_playerAdded(Player &player);
    void server_playerRemoved(int id);

private:
    void closeEvent(QCloseEvent *event);
    Ui::ServerWindow *ui;
    Server server;
};

#endif // SERVERWINDOW_H
