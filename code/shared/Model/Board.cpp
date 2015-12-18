#include "Board.h"

Board::Board()
:QVector<QVector<BoardElement> >()
{
    resize(BOARD_ROWS);
    for (int i = 0; i < BOARD_ROWS; ++i)
        operator[](i).resize(BOARD_COLS);
}

void Board::applyFrame(const QByteArray &frame)
{
    for (int i = 0; i < BOARD_ROWS; ++i){
        for (int j = 0; j < BOARD_COLS; ++j)
             operator[](i)[j].id = frame[i * BOARD_COLS + j];
    }
}

QByteArray Board::getFrame()
{
    QByteArray frame(BOARD_ROWS * BOARD_COLS, '\0');
    for (int i = 0; i < BOARD_ROWS; ++i){
        for (int j = 0; j < BOARD_COLS; ++j)
            frame[i * BOARD_COLS + j] = operator[](i)[j].id;
    }
    return frame;
}
