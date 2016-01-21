#include "Game.h"

#include <QDebug>

Game::Game()
    :status(Game::NO_PLAYING), frameToFrameElapsed(0)
{
}

void Game::handleKeyPress(int key)
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

void Game::handleKeyRelease(int key)
{
    if(status == Game::PLAYING){
        switch (key) {
            case Qt::Key_Up:
                if (player.moving_direction == UP)
                    player.moving_direction = NONE;
                break;
            case Qt::Key_Down:
                if (player.moving_direction == DOWN)
                    player.moving_direction = NONE;
                break;
            case Qt::Key_Left:
                if (player.moving_direction == LEFT)
                    player.moving_direction = NONE;
                break;
            case Qt::Key_Right:
                if (player.moving_direction == RIGHT)
                    player.moving_direction = NONE;
                break;
        }
    }
}

float Game::getPhaseOverlay()
{
    float phaseOverlay = (float)frameUpdateTimer.elapsed() / frameToFrameElapsed;
    return phaseOverlay > 1.0 ? 1.0 : phaseOverlay;
}

void Game::setStatus(Game::STATUS status)
{
    this->status = status;
    if (status == Game::PLAYING)
        frameUpdateTimer.start();
    emit gameStatusChanged(status);
}

void Game::setErrorCode(int errCode)
{
    this->errCode = errCode;
    emit errorCodeChanged(errCode);
}

void Game::applyFrame(const QByteArray &frame)
{
    frameToFrameElapsed = frameUpdateTimer.elapsed();
    frameUpdateTimer.restart();
    model1 = model2;
    model2.applyFrame(frame);
    emit modelActualized();
}
