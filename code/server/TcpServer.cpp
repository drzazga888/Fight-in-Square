#include "TcpServer.h"
#include <QDebug>

TcpServer::TcpServer()
{
    tcpServer=NULL;
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
    if (tcpServer->listen(QHostAddress::Any, port))
    {
        connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
        qDebug() << "server is running...";
		return true;
    }
	else
		return false;
}

bool TcpServer::stop()
{
    qDebug() << "stop function()";
    bool state = false;
    if(tcpServer!=NULL)
    {
        state = disconnectAll();
        tcpServer->close();
        delete tcpServer;
        tcpServer = NULL;
        qDebug() << "server is closing...";
    }
    return state;
}

bool TcpServer::disconnect(int id)
{
    if (connections[id]->getSocket()->state()!=QAbstractSocket::UnconnectedState)
    {
        if (connections[id]->disconnect())
        {
            connections.remove(id);
            return true;
        }
        else return false;
    }
    connections.remove(id);
    return true;
}

bool TcpServer::disconnectAll()
{
    bool state = true;
    QMapIterator<int, Connection*> i(connections);
    while (i.hasNext())
    {
        i.next();
        state = disconnect(i.key());
    }
    return state;
}

void TcpServer::write(int id, QByteArray message)
{
    if(connections[id]->write(message))
        emit writing(id, message);
}

void TcpServer::writeBroadcast(QByteArray message)
{
    QMapIterator<int, Connection*> i(connections);
    while (i.hasNext())
    {
        i.next();
        i.value()->write(message);
    }
	emit broadcasting(message);
}

void TcpServer::acceptConnection()
{
    Connection* conn = new Connection(tcpServer->nextPendingConnection(), 0, Qt::Window);
    conn->setId(connId);
    connections.insert(connId++, conn);
    connect(conn,SIGNAL(reading(int,QByteArray)), this, SLOT(read(int,QByteArray)));
    connect(conn,SIGNAL(disconnecting(int)), this, SLOT(brokeConnection(int)));
    qDebug() << "aaccepting connection...";
}

void TcpServer::read(int id, QByteArray message)
{
	emit reading(id,message);
}

void TcpServer::brokeConnection(int id)
{
    disconnect(id);
    emit disconnecting(id);
}
