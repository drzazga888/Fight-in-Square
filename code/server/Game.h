#ifndef GAME_H
#define GAME_H

#include <QThread>
#include <QWidget>
#include "Network/TcpServer.h"
#include "shared/Network/Protocol.h"
#include "shared/Board.h"
#include "shared/sleep.h"
#include "shared/dialogs/ErrorDialog.h"
#include <iostream>

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
public slots:
	void readData(int,QByteArray);
	void connOrDisconnect();
signals:
	void resultReady(const QString &s);
	void writeData(int,QByteArray);
	void writeBroadcastData(QByteArray);
private:
	Board* board;
	TcpServer* server;
	bool isConnected;
	bool launched;	
};

#endif
