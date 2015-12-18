#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>
#include "../config.h"
#include "Game.h"
#include "Drawer.h"

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(Game *game, QWidget *parent = 0);

private:
    void paintEvent(QPaintEvent *e);
    Drawer drawer;

};

#endif // CANVAS_H
