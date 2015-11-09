#include "TcpServer.h"
#include "iostream"

TcpServer::TcpServer()
{
	connId = 1;
	tcpServer = new QTcpServer(this);
	connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

TcpServer::~TcpServer()
{
	stop();
	connections.clear();
}

bool TcpServer::start(int port)
{
	if (tcpServer->listen(QHostAddress::LocalHost, port))
		return true;
	else
		return false;
}

bool TcpServer::stop()
{
	bool state = disconnectAll();
	tcpServer->close();
	return state;
}

bool TcpServer::disconnect(int id)
{
	if(connections[id]->getSocket()->state()!=QAbstractSocket::UnconnectedState)
	{
		connections[id]->getSocket()->disconnectFromHost();
		delete connections[id];
		connections[id] = NULL;
		connections.remove(id);
		return true;
	}
	return false;
}

bool TcpServer::disconnectAll()
{
	bool state = true;
	for(int i=1;i<connections.size();++i)
	{
		state = disconnect(i);
	}
	return state;
}

void TcpServer::write(int id, QByteArray message)
{
	if(connections[id-1]!=NULL)
	{
		connections[id-1]->write(message);
		emit writing(id,message);
	}
}

void TcpServer::writeBroadcast(QByteArray message)
{
	for(int i=0;i<connections.size();++i)
	{
		if(connections[i]!=NULL)
		{
			connections[i]->write(message);
		}
	}
	emit broadcasting(message);
}

void TcpServer::acceptConnection()
{
	connections.append( new Connection( tcpServer->nextPendingConnection(), 0, Qt::Window ) );
	connections[connId-1]->setId(connId);
	connect(connections[connId-1],SIGNAL(reading(int,QByteArray)), this, SLOT(read(int,QByteArray)));
	++connId;
}

void TcpServer::read(int id, QByteArray message)
{
	emit reading(id,message);
}
