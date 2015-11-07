#ifndef SERVER_FRAME_CODER_H
#define SERVER_FRAME_CODER_H

#include <QObject>

#include "shared/Frames/BoardFrame.h"
#include "shared/Frames/ActionFrame.h"
#include "shared/Board.h"

class ServerFrameCoder : public QObject
{
	Q_OBJECT
public:
	QByteArray encodeBoard(Board* board);
	Frame* decode(QByteArray& frame);
private:

};

#endif