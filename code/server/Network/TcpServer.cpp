#include "TcpServer.h"
#include "iostream"

TcpServer::TcpServer()
{
	
}

TcpServer::~TcpServer()
{
	stop();
	connections.clear();
}

bool TcpServer::start(int port)
{
	connId = 1;
	tcpServer = new QTcpServer(this);
	connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
	if (tcpServer->listen(QHostAddress::LocalHost, port))
		return true;
	else
		return false;
}

bool TcpServer::stop()
{
	bool state = disconnectAll();
	if(tcpServer!=NULL)
	{
		tcpServer->close();
		delete tcpServer;
	}
	return state;
}

bool TcpServer::disconnect(int id)
{
	if(connections[id-1]->getSocket()->state()!=QAbstractSocket::UnconnectedState)
	{
		if(connections[id-1]->disconnect())
		{
			if(connections[id-1]!=NULL)
				delete connections[id-1];
			connections[id-1] = NULL;
			connections.remove(id-1);
			return true;
		}
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
		if(connections[id-1]->write(message))
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
	Connection* conn = new Connection( tcpServer->nextPendingConnection(), 0, Qt::Window);
	connections.append( conn );
	if(connections[connId-1]!=NULL)
	{
		conn->setId(connId);
		connect(conn,SIGNAL(reading(int,QByteArray)), this, SLOT(read(int,QByteArray)));
		connect(conn,SIGNAL(disconnecting(int)), this, SLOT(brokeConnection(int)));
		++connId;
	}
	else
	{
		conn->disconnect();
	}
}

void TcpServer::read(int id, QByteArray message)
{
	emit reading(id,message);
}

void TcpServer::brokeConnection(int id)
{
		emit disconnecting(id);
}