#include "TcpClient.h"

TcpClient::TcpClient()
{
	connected = false;
}

TcpClient::~TcpClient()
{
	
}

void TcpClient::connectToHost(QHostAddress address, int port)
{
	socket = new QTcpSocket(0);
	socket->setReadBufferSize(0);
	connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
	connect(socket, SIGNAL(connected()), this, SLOT(onConnected()));
	connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
	socket->connectToHost(address, port);
}

void TcpClient::disconnectFromHost()
{
	socket->disconnectFromHost();
	socket->abort();
	if(socket!=NULL)
	{
		delete socket;
		socket = NULL;
	}
	emit disconnecting();
}

void TcpClient::write(QByteArray message)
{
	if(connected&&socket!=NULL)
	{
		int ileZapisanych = socket->write(message);
		socket->flush();
		if(ileZapisanych!=-1) {
			emit writing(message);
		}
	}
}

void TcpClient::read()
{
	QByteArray buf = socket->readAll();
	if(buf.size()>0)
		emit reading(buf);
}


void TcpClient::onConnected()
{
	connected = true;
	emit connecting();
}

void TcpClient::onDisconnected()
{
	connected = false;
	emit disconnecting();
}
