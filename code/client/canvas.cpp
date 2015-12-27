#include "canvas.h"

Canvas::Canvas(Game *game, QWidget *parent) :
    QWidget(parent), drawer(game)
{
    setGeometry(CANVAS_PADDING, CANVAS_PADDING, CANVAS_WIDTH, CANVAS_HEIGHT);
    setPalette(QPalette(Qt::black));
    setAutoFillBackground(true);
    connect(game, SIGNAL(gameStatusChanged(Game::STATUS)), this, SLOT(onGameStatusChanged(Game::STATUS)));
}

void Canvas::onGameStatusChanged(Game::STATUS gameStatus)
{
    switch (gameStatus)
    {
    case Game::PLAYING:
        timerId = startTimer(CLIENT_REDRAW_INTERVAL);
        break;
    case Game::DISCONNECTING:
        killTimer(timerId);
        break;
    default:
        break;
    }
}

void Canvas::paintEvent(QPaintEvent *)
{
    drawer.draw(new QPainter(this));
}

void Canvas::timerEvent(QTimerEvent *)
{
    update();
}
