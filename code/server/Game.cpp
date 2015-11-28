#include "Game.h"

Game::Game(QWidget *parent)
: QThread(parent)
{
	launched = true;
    board = new Board(parent);
	board->hide();
    server = new TcpServer();
	coder = new ServerFrameCoder();
	connect(server, SIGNAL(reading(int,QByteArray)), this, SLOT(readData(int,QByteArray)));
	connect(this, SIGNAL(writeData(int,QByteArray)), server, SLOT(write(int,QByteArray)));
	connect(this, SIGNAL(writeBroadcastData(QByteArray)), server, SLOT(writeBroadcast(QByteArray)));
	connect(server, SIGNAL(disconnecting(int)), this, SLOT(brokeConnect(int)));
}

Game::~Game()
{
	delete board;
	delete server;
	delete coder;
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
		Frame* frame = coder->decode(message);std::cout<<"recv:";lookQBA(message);
		if(frame->getType()==Frame::FrameType::Action)//ramka akcji
		{
			if(frame->getActionType() == Frame::ActionType::Connect)//ramka połączenia
			{
				Player *p = new Player(id,frame->getPlayerName());
				Frame::ErrorCode::Code code = board->addPlayer(id,p);
				if(code==Frame::ErrorCode::Undefined)
				{
					emit writeData(id,coder->encodeConnectResp(id));std::cout<<"send:";lookQBA(coder->encodeConnectResp(id));
					logs->append(QString("Nowy gracz: ")+QString(frame->getPlayerName()));
				}
				else
				{
					emit writeData(id,coder->encodeConnectResp(0, code));std::cout<<"send:";lookQBA(coder->encodeConnectResp(0, code));
					if(code==Frame::ErrorCode::MaxPlayers)
					{
						
						logs->append(QString("BŁĄÐ: Przekroczono limit graczy na serwerze"));
						delete p;
						server->disconnect(id);
					}
				}
			}
			else if(frame->getActionType() == Frame::ActionType::Disconnect)//ramka rozłączenia
			{
				Player *p = board->removePlayer(frame->getPlayerId());
				if(p!=NULL)
				{
					logs->append(QString("Opuścił grę: ")+QString(p->getName()));
					delete p;
				}
				else
					logs->append(QString("Opuścił grę: <niezidentyfikowany gracz>"));
				emit writeData(id,coder->encodeDisconnectResp(id));
			}
			else if(frame->getActionType() == Frame::ActionType::Action)//ramka wykonania akcji na planszy
			{
				
			}
		}
		delete frame;
	}
}

void Game::brokeConnect(int id)
{
	Player *p = board->removePlayer(id);
	if(p!=NULL)
	{
		logs->append(QString("Opuścił grę: ")+QString(p->getName()));
		delete p;
	}
}
