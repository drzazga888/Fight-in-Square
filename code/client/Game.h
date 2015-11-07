#ifndef GAME_H
#define GAME_H

#include <QThread>
#include <QWidget>
#include "Network/TcpClient.h"
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
	TcpClient* getClient(){ return client; }
	void close(){ launched=false; }
public slots:
	void readData(QByteArray);
	void connOrDisconnect();
signals:
	void resultReady(const QString &s);
	void writeData(QByteArray);
private:
	Board* board;
	TcpClient* client;
	bool isConnected;
	bool launched;	
};

#endif
