#include "Connection.h"

Connection::Connection(QTcpSocket *inputSocket, QWidget *parent, Qt::WindowFlags f)
{
	setParent(parent, f);
	socket = inputSocket;
	socket->setReadBufferSize(0);
	connect(socket, SIGNAL(readyRead()), this, SLOT(readFromSocket()));
	connect(socket, SIGNAL(disconnected()), this, SLOT(brokeConnection()));
}

Connection::~Connection()
{
	disconnect();
}

bool Connection::disconnect()
{
	if(socket!=NULL)
	{
		socket->disconnectFromHost();
		if(socket->state()==QAbstractSocket::UnconnectedState)
		{
			return true;
		}
	}
	return false;
}

bool Connection::write(QByteArray message)
{
    if(socket!=NULL && socket->state() != QAbstractSocket::UnconnectedState)
	{
		int ileZapisanych = socket->write(message);
		socket->flush();
		if(ileZapisanych!=-1) {
			return true;
		}
	}
	return false;
}

void Connection::readFromSocket()
{
	emit reading(id,socket->readAll());
}

void Connection::brokeConnection()
{
	emit disconnecting(id);
}
