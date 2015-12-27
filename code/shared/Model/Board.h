#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include "../../config.h"
#include "../Frame/Frameable.h"
#include "BoardElements/BoardElement.h"

/**
 * @brief
 * Board przechowuje planszę.
 * Jest to po prostu wektor wektorów, które zawierają
 * obiekty typu BoardElement wzbogacony dodatkowo
 * o możliwość produkcji i przyjmowania ramek.
 */
class Board: public QVector<QVector<BoardElement> >, public Frameable
{

public:
	Board();
	virtual ~Board() {}

    /**
     * @brief applyFrame przyjmuje ramkę i ją aplikuje na obiekt
     * @param frame - ramka
     */
    virtual void applyFrame(const QByteArray &frame);

    /**
     * @brief getFrame tworzy ramkę z obiektu
     * @return ramka
     */
    virtual QByteArray getFrame() const;

};

#endif
