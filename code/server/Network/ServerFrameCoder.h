#ifndef SERVER_FRAME_CODER_H
#define SERVER_FRAME_CODER_H

#include <QObject>

#include "shared/Frames/BoardFrame.h"
#include "shared/Frames/ActionFrame.h"
#include "shared/Frames/OtherFrame.h"
#include "shared/Board.h"
#include <string.h>
#include <iostream>

class ServerFrameCoder : public QObject
{
	Q_OBJECT
public:
	QByteArray encodeBoard(Board* board);
	QByteArray encodeConnectResp(char id, char errorKey=0);
	QByteArray encodeDisconnectResp(char id, char errorKey=0);
	Frame* decode(QByteArray& frame);
private:
	char buffer[256];
};

#endif