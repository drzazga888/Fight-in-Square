#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>

#include "shared/sleep.h"

class TcpClient : public QWidget
{
	Q_OBJECT
public:
	TcpClient();
	~TcpClient();
	void connectToHost(QHostAddress address, int port);
	void disconnectFromHost();
public slots:
	void read();
	void write(QByteArray message);
	void onConnected();
	void onDisconnected();
signals:
	void connecting();
	void disconnecting();
	void reading(QByteArray);
	void writing(QByteArray);
private:
	QTcpSocket* socket;
	bool connected;
};

#endif
