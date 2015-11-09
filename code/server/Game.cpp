#include "Game.h"

Game::Game(QWidget *parent)
: QThread(parent)
{
	launched = true;
	board = new Board(parent);
	board->hide();
	server = new  TcpServer();
	coder = new ServerFrameCoder();
	connect(server, SIGNAL(reading(int,QByteArray)), this, SLOT(readData(int,QByteArray)));
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
		emit writeBroadcastData(coder->encodeBoard(board));
		QThread::msleep(250);
	}
	emit resultReady(result);
}

void Game::readData(int id,QByteArray message)
{
	if(message.size()>1)
	{
		Frame* frame = coder->decode(message);lookQBA(message);
		if(frame->getType()==Frame::FrameType::Action)
		{
			if(frame->getActionType() == Frame::ActionType::Connect)
			{
				Player *p = new Player(id,frame->getPlayerName());
				board->addPlayer(id,p);
				logs->append(QString("Nowy gracz: ")+QString(frame->getPlayerName()));
				emit writeData(id,coder->encodeConnectResp(id));
			}
			else if(frame->getActionType() == Frame::ActionType::Disconnect)
			{
				delete board->removePlayer(frame->getPlayerId());
				logs->append(QString("Nowy gracz: ")+QString(frame->getPlayerName()));
				emit writeData(id,coder->encodeDisconnectResp(id));
			}
			else if(frame->getActionType() == Frame::ActionType::Action)
			{
				
			}
		}
	}
}