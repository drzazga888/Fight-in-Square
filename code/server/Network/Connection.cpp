#include "Connection.h"

Connection::Connection(QTcpSocket *inputSocket, QWidget *parent, Qt::WindowFlags f)
{
	setParent(parent, f);
	socket = inputSocket;
	socket->setReadBufferSize(0);
	connect(socket, SIGNAL(readyRead()), this, SLOT(readFromSocket()));
}

Connection::~Connection()
{
	disconnect();
}

bool Connection::disconnect()
{
	socket->disconnectFromHost();
	if(socket->state()==QAbstractSocket::UnconnectedState)
		return true;
	return false;
}

bool Connection::write(const char* message)
{
	int ileZapisanych = socket->write(message);
	if(ileZapisanych!=-1) {
		emit writing(QByteArray(message));
		return true;
	} else 
		return false;
}

void Connection::readFromSocket()
{
	emit reading(id,socket->readAll());
}
