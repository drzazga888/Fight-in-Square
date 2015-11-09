#ifndef CLIENT_FRAME_CODER_H
#define CLIENT_FRAME_CODER_H

#include <QObject>

#include "shared/Frames/BoardFrame.h"
#include "shared/Frames/ActionFrame.h"
#include "shared/Frames/OtherFrame.h"

class ClientFrameCoder : public QObject
{
	Q_OBJECT
public:
	ClientFrameCoder();
	QByteArray encodeConnect(char* name);
	QByteArray encodeDisconnect();
	QByteArray encodeAction(BoardElement::Direction::DirectionType dir, bool shot);
	void setClientId(char id) { clientId = id; }
	char getClientId(){ return clientId; }
	Frame* decodeMessage(QByteArray frame);
private:
	char clientId;
};

#endif
