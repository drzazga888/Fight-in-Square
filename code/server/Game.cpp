#include "Game.h"

Game::Game(QWidget *parent)
: QThread(parent)
{
	isConnected = false;
	launched = true;
	board = new Board(parent);
	board->hide();
	server = new  TcpServer();
	connect(server, SIGNAL(reading(int,QByteArray)), this, SLOT(readData(int,QByteArray)));
	connect(server, SIGNAL(connecting()), this, SLOT(connOrDisconnect()));
	connect(server, SIGNAL(disconnecting()), this, SLOT(connOrDisconnect()));
	connect(this, SIGNAL(writeData(int,QByteArray)), server, SLOT(write(int,QByteArray)));
	connect(this, SIGNAL(writeBroadcastData(QByteArray)), server, SLOT(writeBroadcast(QByteArray)));
}

Game::~Game()
{
	delete board;
	delete server;
}

void Game::run()
{
	QString result("");
	
	while(launched)
	{
		if(isConnected)
			emit writeBroadcastData(QByteArray("czesc"));
		QThread::msleep(40);
	}
	emit resultReady(result);
}

void Game::readData(int id,QByteArray message)
{
	char* data = message.data();
	std::cout<<data<<std::endl;
}

void Game::connOrDisconnect()
{
	isConnected=!isConnected;
}
