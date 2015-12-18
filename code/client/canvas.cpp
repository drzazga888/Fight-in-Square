#include "canvas.h"

Canvas::Canvas(Game *game, QWidget *parent) :
    QWidget(parent), drawer(game)
{
    setGeometry(CANVAS_PADDING, CANVAS_PADDING, CANVAS_WIDTH, CANVAS_HEIGHT);
    setPalette(QPalette(Qt::black));
    setAutoFillBackground(true);
}

void Canvas::paintEvent(QPaintEvent *e)
{
    drawer.draw(new QPainter(this));
}
