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
protected:
	void closeEvent(QCloseEvent *event);
private:
    Game* game;
    QPushButton* connectButton;
    QPushButton* disconnectButton;
    QLabel* status;
    QLineEdit* host;
    QLineEdit* port;
    ErrorDialog* errorDialog;
};
