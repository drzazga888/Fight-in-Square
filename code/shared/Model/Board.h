#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include "../../config.h"
#include "../Frame/Frameable.h"
#include "BoardElements/BoardElement.h"

class Board: public QVector<QVector<BoardElement> >, public Frameable
{

public:
	Board();
	virtual ~Board() {}

    virtual void applyFrame(const QByteArray &frame);
    virtual QByteArray getFrame();

};

#endif
