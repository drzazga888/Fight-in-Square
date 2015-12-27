#include "Drawer.h"
#include "QBrush"

#include <cmath>
#include <QDebug>

Drawer::Drawer(Game *game)
    :game(game), sprites()
{
}

void Drawer::draw(QPainter *painter)
{
    float phaseOverlay = game->getPhaseOverlay();
    //qDebug() << "paint event, phase overlay = " << phaseOverlay;
    //painter->drawLine(10, 10, phaseOverlay * 200, phaseOverlay * 200);
    painter->drawPoint(cos(phaseOverlay * M_PI * 2.0) * 100 + 150, sin(phaseOverlay * M_PI * 2.0) * 100 + 150);
    painter->drawPixmap(70, 70, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(FLOWERGRASS)));
    painter->drawPixmap(70, 70, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(TANK)));
    // przyklad testowy #1
    qDebug() << "Board test: "
             << game->model2.board[1][2].id
            << ", "
            << game->model2.board[7][9].id
            << ", "
            << game->model2.board[9][13].id; // wall, wall, blank
    // przyklad testowy #2
    foreach (const Player &player, game->model2.players)
    {
        qDebug() << "Gracz #" << player.id << ", zdrowie: " << player.health;
    }
}
