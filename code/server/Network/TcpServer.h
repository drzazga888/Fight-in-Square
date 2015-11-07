#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QVector>
#include <QWidget>
#include <QTcpServer>

#include "Connection.h"

class TcpServer : public QWidget
{
	Q_OBJECT
public:
	TcpServer();
	~TcpServer();
	bool start(int port);
	bool stop();
	bool disconnect(int id);
	bool disconnectAll();
	bool write(int id, const char* message, bool emitable=true);
	bool writeBroadcast(const char* message);
public slots:
	void acceptConnection();
	void read(int,QByteArray);
	void write(int,QByteArray);
	void writeBroadcast(QByteArray);
signals:
	void connecting();
	void disconnecting();
	void reading(int,QByteArray);
	void writing(QByteArray);
	void broadcasting(QByteArray);
private:
	QTcpServer *tcpServer;
	QVector<Connection*> connections;
	int connId;
};

#endif
