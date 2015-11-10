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
	Frame* frame = coder->decodeMessage(message);std::cout<<"recv:";lookQBA(message);
	if(frame->getType()==Frame::FrameType::Action)
	{
		if(frame->getActionType()==Frame::ActionType::Connect)//odpowiedź na połączenie
		{
			if(frame->getErrorCode()==Frame::ErrorCode::Undefined)
				isConnected = true;
			else if(frame->getErrorCode()==Frame::ErrorCode::MaxPlayers)
			{
				if(errorDialog!=NULL)
					delete errorDialog;
				errorDialog = new ErrorDialog("Przekroczono limit graczy na serwerze", "Błąd połączenia");
				errorDialog->show();
				return;
			}
		}
		else if(frame->getActionType()==Frame::ActionType::Disconnect)//odpowiedź na rozłączenie
		{
			isConnected = false;
			client->disconnectFromHost();
		}
	}
}

void Game::connOrDisconnect()
{
	isConnected=!isConnected;
	if(isConnected)
	{
		emit writeData(coder->encodeConnect(playerName));
		std::cout<<"send:";lookQBA(coder->encodeConnect(playerName));
	}
}

void Game::disconnect()
{
	emit writeData(coder->encodeDisconnect());
	std::cout<<"send:";lookQBA(coder->encodeDisconnect());
}

void Game::setPlayerName(QString pn)
{
	strcpy(playerName, pn.toStdString().c_str());
}