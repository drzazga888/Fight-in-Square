#include "Game.h"

#include <QDebug>

Game::Game()
:isRunning(false), model1(), model2(), player(), time()
{

    /* TESTS

    // inicjalizacja testu
    model1 = new Model();
    model1->players[0] = Player(1, Player::RED_GROUP, 210, 90, 30, 3, 15, RIGHT, "Maniek");
    model1->players[1] = Player(2, Player::BLUE_GROUP, 100, 30, 40, 8, 14, UP, "Zygfryd");
    model1->players[2] = Player(3, Player::BLUE_GROUP, 17, 100, 90, 9, 44, DOWN, "Debiii");
    model1->shots.resize(5);
    model1->shots[0] = Shot(2, 3, 16, RIGHT, 17, 30);
    model1->shots[1] = Shot(2, 7, 40, UP, 12, 40);
    model1->shots[2] = Shot(2, 7, 22, UP, 13, 30);
    model1->shots[3] = Shot(1, 11, 12, LEFT, 1, 30);
    model1->shots[4] = Shot(3, 3, 30, DOWN, 1147, 90);
    model1->board[2][2].id = OBSTACLE_BOARD_FIELD;
    model1->board[5][4].id = OBSTACLE_BOARD_FIELD;

    // tworzenie frame-a + spr. parametrow
    QByteArray frame = model1->getFrame();
    qDebug() << "rozmiar: " << frame.size();
    for (int i = 0; i < frame.size(); ++i)
        qDebug() << "[" << i << "] = " << (int)frame[i];

    // tworzenie drugiego modelu na podstawie ramki z pierwszego + spr. parametrów
    model2 = new Model();
    model2->applyFrame(frame);
    qDebug() << "Plansza";
    for (int i = 0; i < BOARD_ROWS; ++i){
        for (int j = 0; j < BOARD_COLS; ++j)
            qDebug() << "[" << i << "][" << j << "] = " << model2->board[i][j].id;
    }
    qDebug() << "Grazce";
    for (int i = 0; i < model2->players.size(); ++i){
        qDebug() << "[" << i << "]";
        qDebug() << "id = " << model2->players[i].id;
        qDebug() << "group = " << model2->players[i].group;
        qDebug() << "points = " << model2->players[i].points;
        qDebug() << "health = " << model2->players[i].health;
        qDebug() << "power = " << model2->players[i].power;
        qDebug() << "x = " << model2->players[i].x;
        qDebug() << "y = " << model2->players[i].y;
        qDebug() << "direction = " << model2->players[i].direction;
        qDebug() << "name = " << model2->players[i].name;
    }
    qDebug() << "Pociski";
    for (int i = 0; i < model2->shots.size(); ++i){
        qDebug() << "[" << i << "]";
        qDebug() << "player_id = " << model2->shots[i].player_id;
        qDebug() << "x_start = " << model2->shots[i].x_start;
        qDebug() << "y_start = " << model2->shots[i].y_start;
        qDebug() << "direction = " << model2->shots[i].direction;
        qDebug() << "flight_periods = " << model2->shots[i].flight_periods;
        qDebug() << "power = " << model2->shots[i].power;
    }

    // test kopiowania
    Model temp = *model1;

    */

}

void Game::handleKeyboard(int key)
{
    if(isRunning){
        switch (key) {
            case Qt::Key_Up:
                player.moving_direction = UP;
                break;
            case Qt::Key_Down:
                player.moving_direction = DOWN;
                break;
            case Qt::Key_Left:
                player.moving_direction = LEFT;
                break;
            case Qt::Key_Right:
                player.moving_direction = RIGHT;
                break;
            case Qt::Key_Space:
                player.player_shooted = true;
                break;
        }
    }
}

float Game::getPhaseOverlay()
{
    return (float)time.elapsed() / SERVER_SEND_INTERVAL;
}
