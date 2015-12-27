#include "Model.h"

Model::Model()
{
}

void Model::applyFrame(const QByteArray &frame)
{
    int ptr = 1, size;
    board.applyFrame(QByteArray(frame.data() + ptr, BOARD_COLS * BOARD_ROWS));
    ptr += BOARD_COLS * BOARD_ROWS;
    size = frame[ptr++];
    players.clear();
    for (int i = 0; i < size; ++i){
        players.insert(frame[ptr], QByteArray(frame.data() + ptr, 26));
        ptr += 26;
    }
    shots.resize(frame[ptr++]);
    for (int i = 0; i < shots.size(); ++i){
        shots[i].applyFrame(QByteArray(frame.data() + ptr, 9));
        ptr += 9;
    }
}

QByteArray Model::getFrame() const
{
    int n = 3 + BOARD_COLS * BOARD_ROWS + shots.size() * 9 + players.size() * 26;
    int ptr = 0;
    QByteArray frame(n, '\0');
    frame[ptr++] = 2;
    frame.insert(ptr, board.getFrame());
    ptr += BOARD_COLS * BOARD_ROWS;
    frame[ptr++] = players.size();
    QMapIterator<int, Player> i(players);
    while (i.hasNext())
    {
        i.next();
        frame.insert(ptr, i.value().getFrame());
        ptr += 26;
    }
    frame[ptr++] = shots.size();
    for (int i = 0; i < shots.size(); ++i){
        frame.insert(ptr, shots[i].getFrame());
        ptr += 9;
    }
    frame.resize(n);
    return frame;
}
