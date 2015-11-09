#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QStatusBar>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QHostAddress>

#include "Game.h"
#include "Network/TcpClient.h"
#include "shared/Board.h"
#include "shared/sleep.h"
#include "shared/dialogs/ErrorDialog.h"
#include <iostream>

class Client : public QMainWindow {
  Q_OBJECT
public:
    Client();
    ~Client();
	void run();
public slots:
    void connectToServer();
    void disonnectFromServer();
    void handleResults(QString r);
    void detectConnecting();
    void detectDisconnecting();
protected:
	void closeEvent(QCloseEvent *event);
    void keyPressEvent( QKeyEvent *k );
private:
    Game* game;
    QPushButton* connectButton;
    QPushButton* disconnectButton;
    QLabel* status;
    QLineEdit* playerName;
    QLineEdit* host;
    QLineEdit* port;
    ErrorDialog* errorDialog;
    bool isConnected;
};
