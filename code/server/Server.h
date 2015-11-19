#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QStatusBar>
#include <QLineEdit>
#include <QTextEdit>
#include <QHostAddress>
#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>

#include "Game.h"
#include "shared/Board.h"
#include "Network/TcpServer.h"
#include "shared/sleep.h"
#include "shared/dialogs/ErrorDialog.h"

class Server : public QMainWindow {
  Q_OBJECT
public:
    Server();
    ~Server();
public slots:
    void startServer();
    void stopServer();
    void read(int,QByteArray);
    void handleResults(QString r);
protected:
	void closeEvent(QCloseEvent *event);
private:
	Game* game;
	QPushButton* startButton;
	QPushButton* stopButton;
	QLabel* status;
	QLineEdit* port;
	QTextEdit* logs;
	ErrorDialog* errorDialog;
	QWidget *window;
	QVBoxLayout *lay;
};

#endif
