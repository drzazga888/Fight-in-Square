#ifndef GAME_H
#define GAME_H

#include <QThread>
#include <QTextEdit>
#include <QWidget>
#include "Network/TcpServer.h"
#include "Network/ServerFrameCoder.h"
#include "shared/Board.h"
#include "shared/sleep.h"
#include "shared/dialogs/ErrorDialog.h"
#include "shared/GameElements/BoardElement.h"
#include "shared/lookQBA.h"

class Game : public QThread
{
	Q_OBJECT
public:
	Game(QWidget *parent = 0);
	~Game();
	void run();
	Board* getBoard(){ return board; }
	TcpServer* getServer(){ return server; }
	void close(){ launched=false; }
	void setLogOutput(QTextEdit *l){ logs = l; }
public slots:
	void readData(int,QByteArray);
signals:
	void resultReady(const QString &s);
	void writeData(int,QByteArray);
	void writeBroadcastData(QByteArray);
private:
	Board* board;
	TcpServer* server;
	ServerFrameCoder* coder;
	bool launched;
	QTextEdit *logs;
};

#endif
