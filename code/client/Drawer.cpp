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

    paint_background(painter,game->model2.board);

    draw_players(painter,game->model1.players,game->model2.players,phaseOverlay);

    draw_bullets(painter,game->model2.shots);

}


void Drawer::draw_players(QPainter *painter, QMap<int, Player> players1, QMap<int,Player> players2, float phase)
{
    QTransform transf;
    int x1,y1,x2,y2,delta_x,delta_y;

    foreach (const Player player, players1)
        {
        x1 = cast_to_pixels(player.x);
        y1 = cast_to_pixels(player.y);
        x2 = cast_to_pixels(players2[player.id].x);
        y2 = cast_to_pixels(players2[player.id].y);
        delta_x = x2-x1;
        delta_y = y2-y1;
             transf.reset();
         if(player.direction && player.health > 0)
            {
            painter->drawPixmap(
                        x1+delta_x*phase,
                        y1+delta_y*phase,
                        BOARD_FIELD_WIDTH,
                        BOARD_FIELD_HEIGHT,
                        sprites.get(TANK_BOARD_FIELD_ID).transformed(transf.rotate(90*(player.direction-1))));
            }
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
/*void Drawer::draw_players(QPainter *painter, QMap<int, Player> players)
{
    QTransform transf;
    //QPixmap mask(BOARD_FIELD_WIDTH,BOARD_FIELD_HEIGHT);

    foreach (const Player player, players)
        {
         transf.reset();
         if(player.direction && player.health > 0)
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
*/
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
                        cast_to_pixels(shots[i].x_start+step_x+pos_x),
                        cast_to_pixels(shots[i].y_start+step_y+pos_y),
                        BOARD_FIELD_WIDTH,
                        BOARD_FIELD_HEIGHT,
                        sprites.get(BULLET_BOARD_FIELD_ID).transformed(trans.rotate(90*(shots[i].direction-1))));

    }
}

int Drawer::cast_to_pixels(int x)
{
       return (x-2)*BOARD_FIELD_WIDTH/5;
}
