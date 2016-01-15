#include "Game.h"

#include <QDebug>

Game::Game()
    :status(Game::NO_PLAYING), frameToFrameElapsed(0)
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
    return (float)frameUpdateTimer.elapsed() / frameToFrameElapsed;
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
    frameToFrameElapsed = frameUpdateTimer.elapsed();
    qDebug() << frameToFrameElapsed;
    frameUpdateTimer.restart();
    model1 = model2;
    model2.applyFrame(frame);
    emit modelActualized();
}
