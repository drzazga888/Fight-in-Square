#include "Drawer.h"
#include "QBrush"

#include <QDebug>

Drawer::Drawer(Game *game)
    :game(game), sprites()
{
}

void Drawer::draw(QPainter *painter)
{
    float phaseOverlay = game->getPhaseOverlay();
    game->model1.board[2][3];
    qDebug() << "paint event, phase overlay = " << phaseOverlay;
    painter->drawLine(10, 10, 40, 40);
    painter->drawPixmap(70, 70, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(FLOWERGRASS)));
painter->drawPixmap(140, 140, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(FLOWERGRASS)));
    painter->drawPixmap(70, 70, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(TANK)));
}
