#ifndef BOARDELEMENT_H
#define BOARDELEMENT_H

#include <QString>
#include <QPainter>
#include "../../../config.h"

/**
 * @brief
 * Klasa przechowuje informacje o polu planszy.
 * W swej podstawowej wersji jest to tylko id pola.
 */
class BoardElement
{

public:
    BoardElement(int id = BOARD_FIELD_ID(EMPTY));
    virtual ~BoardElement(){}

    /**
     * @brief id Identyfikator elementu planszy
     */
    unsigned char id;

};

#endif // BOARDELEMENT_H
