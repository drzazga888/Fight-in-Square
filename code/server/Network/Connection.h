#ifndef CONNECTION_H
#define CONNECTION_H

#include <QWidget>
#include <QTcpSocket>

class Connection : public QWidget
{
	Q_OBJECT
public:
	Connection(QTcpSocket *inputSocket = NULL, QWidget *parent = 0, Qt::WindowFlags f = 0);
	~Connection();
	QTcpSocket* getSocket() { return socket; }
	void setId(int connId){ id = connId; }
	int getId() { return id; }
	bool disconnect();
	bool write(const char* message);
public slots:
	void readFromSocket();
signals:
	void reading(int,QByteArray);
	void writing(QByteArray);
private:
	QTcpSocket *socket;
	int id;
};

#endif
