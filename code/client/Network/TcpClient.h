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
	bool connectToHost(QHostAddress address, int port);
	bool disconnectFromHost();
public slots:
	void read();
	void write(QByteArray message);
signals:
	void connecting();
	void disconnecting();
	void reading(QByteArray);
	void writing(QString);
private:
	QTcpSocket* socket;
	bool connected;
};

#endif
