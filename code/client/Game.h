#ifndef GAME_H
#define GAME_H

#include <QThread>
#include <QWidget>
#include "Network/TcpClient.h"
#include "Network/ClientFrameCoder.h"
#include "shared/Board.h"
#include "shared/sleep.h"
#include "shared/dialogs/ErrorDialog.h"
#include "shared/GameElements/BoardElement.h"
#include "shared/lookQBA.h"
#include <string>
#include <string.h>

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
	void move(BoardElement::Direction::DirectionType d) { dir = d; isAction = true; };
	void shot() { shotted = true; isAction = true; };
	void disconnect();
	void setPlayerName(QString pn);
public slots:
	void readData(QByteArray);
	void connOrDisconnect();
signals:
	void resultReady(const QString &s);
	void writeData(QByteArray);
private:
	Board* board;
	ClientFrameCoder* coder;
	TcpClient* client;
	bool isConnected;
	bool launched;

	bool isAction;
	bool shotted;
	BoardElement::Direction::DirectionType dir;
	char playerName[256];
};

#endif
