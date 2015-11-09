#include "Game.h"

Game::Game(QWidget *parent)
: QThread(parent)
{
	isConnected = false;
	launched = true;
	board = new Board(parent);
	board->show();
	client = new  TcpClient();
	coder = new ClientFrameCoder();
	dir = BoardElement::Direction::None;
	shotted = false;
	isAction = false;
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
		if(isConnected&&isAction)
		{
			emit writeData(coder->encodeAction(dir, shotted));
			lookQBA(coder->encodeAction(dir, shotted));
			dir = BoardElement::Direction::None;
			shotted = false;
			isAction = false;
		}
		QThread::msleep(40);
	}
	emit resultReady(result);
}

void Game::readData(QByteArray message)
{
	Frame* frame = coder->decodeMessage(message);lookQBA(message);
	if(frame->getType()==Frame::FrameType::Action)
	{
		if(frame->getActionType()==Frame::ActionType::Connect)//odpowiedź na połączenie
		{
			isConnected = true;
		}
		else if(frame->getActionType()==Frame::ActionType::Disconnect)//odpowiedź na rozłączenie
		{
			isConnected = false;
		}
	}
}

void Game::connOrDisconnect()
{
	if(!isConnected)
		emit writeData(coder->encodeConnect(playerName));
	else
		emit writeData(coder->encodeDisconnect());
}

void Game::disconnect()
{
	emit writeData(coder->encodeDisconnect());
	client->disconnectFromHost();
}

void Game::setPlayerName(QString pn)
{
	strcpy(playerName, pn.toStdString().c_str());
}