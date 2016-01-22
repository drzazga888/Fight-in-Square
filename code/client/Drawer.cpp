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

    draw_bullets(painter,game->model1.shots,game->model2.shots,phaseOverlay);

    draw_animation(painter,animations);
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
         else
             qDebug() << "nie wchodzę do funkcji rysującej, a direction to:" << player.direction;
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

void Drawer::draw_bullets(QPainter *painter, QMap<int, Shot> &shots1, QMap<int, Shot> &shots2, float phase)
{
    int step_x=0;
    int step_y=0;
    int pos_x=0;
    int pos_y=0;
    int flight_periods;
    int anim_x=0;
    int anim_y=0;
    bool animate = true;
    QTransform trans;


    foreach(const Shot shot, shots1)
    {

        animate=true;
        step_x=0;
        step_y=0;

        pos_x=0;
        pos_y=0;

        anim_x=0;
        anim_y=0;

        if(shots2.contains(shot.id)){
        flight_periods = cast_to_pixels(shots2[shot.id].flight_periods - shot.flight_periods)*phase;
        }
        else
            flight_periods = 0;//cast_to_pixels(shot.flight_periods);

        switch(shot.direction)
        {
        case UP:
            step_y=-(cast_to_pixels(shot.flight_periods)+flight_periods);
            pos_y=-2;
            anim_y=-3;
            break;
        case DOWN:
            pos_y=2;
            step_y=(cast_to_pixels(shot.flight_periods)+flight_periods);
            anim_y=3;
            break;
        case LEFT:
            pos_x=-2;
            step_x=-(cast_to_pixels(shot.flight_periods)+flight_periods);
            anim_x=-3;
            break;
        case RIGHT:
            pos_x=2;
            anim_x=3;
            step_x=(cast_to_pixels(shot.flight_periods)+flight_periods);
            break;
        default:
            anim_x=0;
            anim_y=0;
            pos_x=0;
            pos_y=0;
            step_x=0;
            step_y=0;
            break;
        }
        trans.reset();
      //  int static n=0;

        foreach (const Shot shott, shots2) {
         if(shott.id == shot.id){
             animate=false;
                break;
         }//else animate = true;
        }

        if(animate)
        {

        animations.append(Animation(
                              cast_to_pixels(shot.x_start+pos_x+anim_x)+step_x,
                              cast_to_pixels(shot.y_start+pos_y+anim_y)+step_y));
        }
                painter->drawPixmap(
                         cast_to_pixels(shot.x_start+pos_x)+step_x,
                        cast_to_pixels(shot.y_start+pos_y)+step_y,
                        BOARD_FIELD_WIDTH,
                        BOARD_FIELD_HEIGHT,
                        sprites.get(BULLET_BOARD_FIELD_ID).transformed(trans.rotate(90*(shot.direction-1))));

    }

}

int Drawer::cast_to_pixels(int x)
{
       return (x-2)*BOARD_FIELD_WIDTH/5;
}


void Drawer::draw_animation(QPainter *painter, QList<Animation> &animations){

    QMutableListIterator<Animation> ian(animations);
            while(ian.hasNext()){
    Animation an = ian.next();
        painter->drawPixmap(
            an.getplacex(),
            an.getplacey(),
            BOARD_FIELD_WIDTH,
            BOARD_FIELD_HEIGHT,
            sprites.get(an.getPhase()));

        an.changePhase();
        if(an.getPhase() == EMPTY_BOARD_FIELD_ID)
            ian.remove();
        else
            ian.setValue(an);
    }
}
