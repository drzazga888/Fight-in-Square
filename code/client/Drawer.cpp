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
    static float lastphase = 0;
    static QVector<Shot>shot_copy;
    /****** Kasia test *********/

   /* for(int a=0; a<BOARD_COLS;a++)
        for(int b=0; b<BOARD_ROWS;b++)
        {
            game->model1.board[b][a]=(a+b)%4+1;
        }

    */
    paint_background(painter,game->model2.board);

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
  /***
      game->model2.players[0].y+=1;
      game->model2.players[1].x+=1;
    */
  draw_players(painter,game->model2.players);
// przyklad testowy #3 - sprawdzanie, ile zycia zzera mi serwer...

    draw_bullets(painter,game->model2.shots);
   lastphase = phaseOverlay;
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
            if(col> BOARD_COLS || col2> BOARD_COLS || row>BOARD_ROWS || row2 > BOARD_ROWS )
                return true;
           else if(game->model2.board[col][row].id==5 || game->model2.board[col2][row2].id==5)
            {
                 return true;
            }
        }
        else if(type == TUNK_TYPE)
        {

        }
     return false;
}

void Drawer::which_field(int &col, int &row, int x, int y)
    {

    if(cast_to_pixels(x)>CANVAS_PADDING && cast_to_pixels(y)>CANVAS_PADDING){
    col = (cast_to_pixels(x)-CANVAS_PADDING)%BOARD_FIELD_WIDTH;
    col = (cast_to_pixels(x)-col-CANVAS_PADDING)/BOARD_FIELD_WIDTH-1;
    row = (cast_to_pixels(y)-CANVAS_PADDING)%BOARD_FIELD_HEIGHT;
    row = (cast_to_pixels(y)-row-CANVAS_PADDING)/BOARD_FIELD_HEIGHT-1;
        }
    else
            {
                    col=BOARD_COLS+1;
                    row=BOARD_ROWS+1;
            }
}
void Drawer::draw_players(QPainter *painter, QMap<int, Player> players)
{
    QTransform transf;

    foreach (const Player player, players)
        {

         if(player.direction)
            {
            painter->drawPixmap(
                        cast_to_pixels(player.x),
                        cast_to_pixels(player.y),
                        BOARD_FIELD_WIDTH,
                        BOARD_FIELD_HEIGHT,
                        sprites.get(TANK_BOARD_FIELD_ID).transformed(transf.rotate(90*(player.direction-1))));
            }
    }
}

void Drawer::draw_bullets(QPainter *painter, QVector<Shot> &shots)
{
    int step_x=0;
    int step_y=0;
    int pos_x=0;
    int pos_y=0;
    QTransform trans;

    for(int i=0;i<shots.size();i++)
    {

        step_x=0;
        step_y=0;

        pos_x=0;
        pos_y=0;

        switch(shots[i].direction)
        {
        case UP:
            step_y=-shots[i].flight_periods;
            pos_y=-2;
            break;
        case DOWN:
            pos_y=2;
            step_y=shots[i].flight_periods;
            break;
        case LEFT:
            pos_x=-2;
            step_x=-shots[i].flight_periods;
            break;
        case RIGHT:
            pos_x=2;
            step_x=shots[i].flight_periods;
            break;
        default:
            pos_x=0;
            pos_y=0;
            step_x=0;
            step_y=0;
            break;
        }
trans.reset();
        //if(check_collisions(shots[i].x_start+step_x,shots[i].y_start+step_y,shots[i].direction))
        //{
        //animations.append(Animation(shots[i].x_start,shots[i].y_start));
        //}
        //else
                painter->drawPixmap(
                        cast_to_pixels(shots[i].x_start+step_x+pos_x,shots[i].direction),
                        cast_to_pixels(shots[i].y_start+step_y+pos_y,shots[i].direction),
                        BOARD_FIELD_WIDTH,
                        BOARD_FIELD_HEIGHT,
                        sprites.get(BULLET_BOARD_FIELD_ID).transformed(trans.rotate(90*(shots[i].direction-1))));
qDebug() << shots[i].direction;
    }
}

int Drawer::cast_to_pixels(int x,DIRECTION direction)
{

        switch (direction) {
        case UP:
        case LEFT:
            return (x)*BOARD_FIELD_WIDTH/5-BOARD_FIELD_WIDTH/5*2;
        case DOWN:
        case RIGHT:
            return (x)*BOARD_FIELD_WIDTH/5-BOARD_FIELD_WIDTH/5*2;
        default:
        return (x-2)*BOARD_FIELD_WIDTH/5;
            break;
        }
}
