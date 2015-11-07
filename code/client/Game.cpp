#include "Game.h"

Game::Game(QWidget *parent)
: QThread(parent)
{
	isConnected = false;
	launched = true;
	board = new Board(parent);
	board->show();
	client = new  TcpClient();
	connect(client, SIGNAL(reading(QByteArray)), this, SLOT(readData(QByteArray)));
	connect(client, SIGNAL(connecting()), this, SLOT(connOrDisconnect()));
	connect(client, SIGNAL(disconnecting()), this, SLOT(connOrDisconnect()));
	connect(this, SIGNAL(writeData(QByteArray)), client, SLOT(write(QByteArray)));
}

Game::~Game()
{
	delete board;
	delete client;
}

void Game::run()
{
	QString result("");
	
	while(launched)
	{
		if(isConnected)
			emit writeData(QByteArray("czesc"));
		QThread::msleep(40);
	}
	emit resultReady(result);
}

void Game::readData(QByteArray message)
{
	char* data = message.data();
	std::cout<<data<<std::endl;
}

void Game::connOrDisconnect()
{
	isConnected=!isConnected;
}
