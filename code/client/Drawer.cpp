#include "Drawer.h"
#include "QBrush"

#include <QDebug>

Drawer::Drawer(Game *game)
    :game(game), sprites()
{
}

void Drawer::paint_background(QPainter *painter, const Board &board)
{
  //  try{
    int x,y;
    for(int i=CANVAS_PADDING,x=0;i<CANVAS_WIDTH;i+=BOARD_FIELD_WIDTH,x++)
        for(int j=CANVAS_PADDING,y=0;j<CANVAS_HEIGHT;j+=BOARD_FIELD_HEIGHT,y++){
   // if(sprites.get(board[x][y].id))
            painter->drawPixmap(i,j,BOARD_FIELD_WIDTH,BOARD_FIELD_HEIGHT, sprites.get(board[x][y].id));
/*}
    }catch(...){
        std::cout << "Brak odpowiedniego sprite'a" << std::endl;
    }*/
    }
}

void Drawer::draw(QPainter *painter)
{
    float phaseOverlay = game->getPhaseOverlay();
    game->model1.board[2][3];
    qDebug() << "paint event, phase overlay = " << phaseOverlay;
    painter->drawLine(10, 10, 40, 40);

    paint_background(painter,game->model1.board);
    QTransform transf;
    painter->drawPixmap(70, 70, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(FLOWERGRASS)));
    painter->drawPixmap(70, 140, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(GRASS)));
    painter->drawPixmap(70, 70, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(TANK)).transformed(transf.rotate(45)));
painter->drawPixmap(70, 140, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(TANK)));
}
