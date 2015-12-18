#ifndef BOARDELEMENT_H
#define BOARDELEMENT_H

#include <QString>
#include <QPainter>
#include "../../../config.h"

class BoardElement
{

public:
    BoardElement(int id = BOARD_FIELD_ID(EMPTY), QString path = QString());
    virtual ~BoardElement(){}

    unsigned char id;
    QString path;

};

#endif // BOARDELEMENT_H
