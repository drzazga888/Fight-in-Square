#include "Drawer.h"
#include "QBrush"

#include <cmath>
#include <QDebug>

Drawer::Drawer(Game *game)
    :game(game), sprites()
{
}

void Drawer::paint_background(QPainter *painter, const Board &board)
{
    for (int i = 0; i < BOARD_ROWS; ++i)
    {
        for (int j = 0; j < BOARD_COLS; ++j)
            painter->drawPixmap(
                j * BOARD_FIELD_WIDTH,
                i * BOARD_FIELD_HEIGHT,
                BOARD_FIELD_WIDTH,
                BOARD_FIELD_HEIGHT,
                sprites.get(board[i][j].id)
            );
    }
}

void Drawer::draw(QPainter *painter)
{
    float phaseOverlay = game->getPhaseOverlay();
    paint_background(painter,game->model1.board);
    QTransform transf;
    painter->drawPixmap(70, 70, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(FLOWERGRASS)));
    painter->drawPixmap(70, 140, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(GRASS)));
    painter->drawPixmap(70, 70, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(TANK)).transformed(transf.rotate(45)));
	painter->drawPixmap(70, 140, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(TANK)));

	/*********** TESTY KAMILSON-A ***********/

	// przyklad testowy #1 - animująca się kropka ok. 60 fps
	painter->drawPoint(cos(phaseOverlay * M_PI * 2.0) * 100 + 150, sin(phaseOverlay * M_PI * 2.0) * 100 + 150);
    painter->drawPixmap(70, 70, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(TANK)));

    // przyklad testowy #2 - sprawdzanie, co jest pod board
    qDebug() << "Board test: "
             << game->model2.board[1][2].id
            << ", "
            << game->model2.board[7][9].id
            << ", "
            << game->model2.board[9][13].id; // wall, wall, blank

    // przyklad testowy #3 - sprawdzanie, ile zycia zzera mi serwer...
    foreach (const Player &player, game->model2.players)
    {
        qDebug() << "Gracz #" << player.id << ", zdrowie: " << player.health;
    }

}
