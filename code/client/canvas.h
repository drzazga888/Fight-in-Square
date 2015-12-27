#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QPainter>
#include <QPalette>
#include "../config.h"
#include "Game.h"
#include "Drawer.h"

/**
 * @brief
 * Klasa ta jest widgetem-płótnem, na którym malowana
 * jest plansza z grą.
 * W określonych przedziałach czasu wywoływane jest zdarzenie
 * malowania, które przekazuje pałeczkę obiektowi drawer.
 */
class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(Game *game, QWidget *parent = 0);

public slots:
    /**
     * @brief
     * Slot, który podpięty jest pod zmianę stanu gry.
     * @param gameStatus
     * nowy status gry
     */
    void onGameStatusChanged(Game::STATUS gameStatus);

private:

    /**
     * @brief Zdarzenie malowania
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief
     * Regularne zdarzenie czasowe, które zmusza Qt
     * do przemalowania płótna.
     */
    void timerEvent(QTimerEvent *);
    Drawer drawer;

    int timerId;

};

#endif // CANVAS_H
