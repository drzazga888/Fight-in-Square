#include "Game.h"

#include <QDebug>

Game::Game()
    :status(Game::NO_PLAYING)
{



}

void Game::handleKeyboard(int key)
{
    if(status == Game::PLAYING){
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
    return (float)frameUpdateTimer.elapsed() / SERVER_SEND_INTERVAL;
}

void Game::setStatus(Game::STATUS status)
{
    this->status = status;
    //qDebug() << status;
    if (status == Game::PLAYING)
        frameUpdateTimer.start();
    emit gameStatusChanged(status);
}

void Game::applyFrame(const QByteArray &frame)
{
    qDebug() << frameUpdateTimer.elapsed();
    frameUpdateTimer.restart();
    model1 = model2;
    model2.applyFrame(frame);
    emit modelActualized();
}
