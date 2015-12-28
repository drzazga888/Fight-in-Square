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
    float lastphase;
    //Kasia test
    for(int a=0; a<BOARD_COLS;a++)
        for(int b=0; b<BOARD_ROWS;b++)
        {
            game->model1.board[b][a]=(a+b)%4+1;
     //    qDebug() << game->model1.board[b][a].id;
        }
    paint_background(painter,game->model1.board);
    //QTransform transf;
    //painter->drawPixmap(70, 70, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(FLOWERGRASS)));
    //painter->drawPixmap(70, 140, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(GRASS)));
    //painter->drawPixmap(70, 70, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(TANK)).transformed(transf.rotate(45)));
    //painter->drawPixmap(70, 140, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(TANK)));

	/*********** TESTY KAMILSON-A ***********/

	// przyklad testowy #1 - animująca się kropka ok. 60 fps
    //painter->drawPoint(cos(phaseOverlay * M_PI * 2.0) * 100 + 150, sin(phaseOverlay * M_PI * 2.0) * 100 + 150);
   // painter->drawPixmap(70, 70, BOARD_FIELD_WIDTH, BOARD_FIELD_HEIGHT, sprites.get(BOARD_FIELD_ID(TANK)));

    // przyklad testowy #2 - sprawdzanie, co jest pod board
    /* qDebug() << "Board test: "
             << game->model2.board[1][2].id
            << ", "
            << game->model2.board[7][9].id
            << ", "
            << game->model2.board[9][13].id; // wall, wall, blank
*/
    //test draw_players
//if(lastphase+1 < phaseOverlay)
//{
    game->model2.players[0].y+=1;
    game->model2.players[1].x+=1;
    lastphase=phaseOverlay;
//}
draw_players(painter,game->model2.players);
    // przyklad testowy #3 - sprawdzanie, ile zycia zzera mi serwer...
    foreach (const Player &player, game->model2.players)
    {
        qDebug() << "Gracz #" << player.id << ", zdrowie: " << player.health << ", x:"<< player.x << ", y:" << player.y;

    }

}


bool Drawer::check_collisions(unsigned char x, unsigned char y, int type, DIRECTION direction){

    int col, row, col2, row2;
int x2, y2,a;
if(type== BULLET_TYPE)
    a=5;
else
    a=1;
    switch(direction)
    {
    case NONE:
        return false;
        break;
    case UP:
      x2=x+BOARD_FIELD_WIDTH/a;
      y2=y;
        break;
    case DOWN:
        x2=x+BOARD_FIELD_WIDTH/a;
        y2=y+BOARD_FIELD_HEIGHT/a;
        y=y2;
        break;
    case LEFT:
        x2=x;
        y2=y+BOARD_FIELD_HEIGHT/a;
        break;
    case RIGHT:
         x2=x+BOARD_FIELD_WIDTH/a;
         x=x2;
         y2=y+BOARD_FIELD_HEIGHT/a;
        break;
    }

        if(type == BULLET_TYPE)
        {
            which_field(col,row,x,y);
            which_field(col2,row2,x2,y2);
            if(game->model2.board[col][row].id==5 || game->model2.board[col2][row2].id==5)
            {
                 return true;
            }
        }
        else if(type == TUNK_TYPE)
        {

        }
     return false;
}

void Drawer::which_field(int &col, int &row, int x, int y){
    col = (x-CANVAS_PADDING)%BOARD_FIELD_WIDTH;
    col = (x-col-CANVAS_PADDING)/BOARD_FIELD_WIDTH-1;
    row = (y-CANVAS_PADDING)%BOARD_FIELD_HEIGHT;
    row = (y-row-CANVAS_PADDING)/BOARD_FIELD_HEIGHT-1;
}

void Drawer::draw_players(QPainter *painter, QMap<int, Player> players)
{
    QTransform transf;
    for(int i=players.count()-1;i>=0;i--)
        {
         if(players[i].direction)
            {
            painter->drawPixmap(
                        players[i].x,
                        players[i].y,
                        BOARD_FIELD_WIDTH,
                        BOARD_FIELD_HEIGHT,
                        sprites.get(TANK_BOARD_FIELD_ID).transformed(transf.rotate(90*(players[i].direction-1))));
            }
    }
}
