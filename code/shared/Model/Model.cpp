#include "Model.h"

Model::Model()
{
}

void Model::applyFrame(const QByteArray &frame)
{
    int ptr = 1;
    board.applyFrame(QByteArray(frame.data() + ptr, BOARD_COLS * BOARD_ROWS));
    ptr += BOARD_COLS * BOARD_ROWS;
    players.resize(frame[ptr++]);
    for (int i = 0; i < players.size(); ++i){
        players[i].applyFrame(QByteArray(frame.data() + ptr, 24));
        ptr += 24;
    }
    shots.resize(frame[ptr++]);
    for (int i = 0; i < shots.size(); ++i){
        shots[i].applyFrame(QByteArray(frame.data() + ptr, 9));
        ptr += 9;
    }
}

QByteArray Model::getFrame()
{
    int n = 3 + BOARD_COLS * BOARD_ROWS + shots.size() * 9 + players.size() * 24;
    int ptr = 0;
    QByteArray frame(n, '\0');
    frame[ptr++] = 2;
    frame.insert(ptr, board.getFrame());
    ptr += BOARD_COLS * BOARD_ROWS;
    frame[ptr++] = players.size();
    for (int i = 0; i < players.size(); ++i){
        frame.insert(ptr, players[i].getFrame());
        ptr += 24;
    }
    frame[ptr++] = shots.size();
    for (int i = 0; i < shots.size(); ++i){
        frame.insert(ptr, shots[i].getFrame());
        ptr += 9;
    }
    frame.resize(n);
    return frame;
}
