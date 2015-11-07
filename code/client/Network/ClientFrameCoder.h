#ifndef CLIENT_FRAME_CODER_H
#define CLIENT_FRAME_CODER_H

#include <QObject>

#include "shared/Frames/BoardFrame.h"
#include "shared/Frames/ActionFrame.h"

class ClientFrameCoder : public QObject
{
	Q_OBJECT
public:
	ClientFrameCoder(int gamerId);
	QByteArray encodeConnect();
	QByteArray encodeDisconnect();;
	QByteArray encodeAction();
private:

};

#endif
