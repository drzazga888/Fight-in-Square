#include "TcpClient.h"

TcpClient::TcpClient()
{
	connected = false;
}

TcpClient::~TcpClient()
{
	
}

bool TcpClient::connectToHost(QHostAddress address, int port)
{
	socket = new QTcpSocket(0);
	socket->setReadBufferSize(0);
	connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
	socket->connectToHost(address, port);
	if(socket->state()!=QAbstractSocket::UnconnectedState)
	{
		connected = true;
		emit connecting();
		return true;
	}
	return false;
}

bool TcpClient::disconnectFromHost()
{
	connected = false;
	socket->disconnectFromHost();
	socket->abort();
	if(socket!=NULL)
	{
		delete socket;
		socket = NULL;
	}
	emit disconnecting();
	return true;
}

void TcpClient::write(QByteArray message)
{
	if(connected)
	{
		int ileZapisanych = socket->write(message);
		socket->flush();
		if(ileZapisanych!=-1) {
			emit writing(QString(message));
		}
	}
}

void TcpClient::read()
{
	QByteArray buf = socket->readAll();
	if(buf.size()>0)
		emit reading(buf);
}
