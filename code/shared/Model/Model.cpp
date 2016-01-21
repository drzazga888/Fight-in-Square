#include "Model.h"

Model::Model()
{
}

void Model::applyFrame(const QByteArray &frame)
{
    int ptr = 1, size;
    if (frame[0] == 2)
    {
        board.applyFrame(QByteArray(frame.data() + ptr, BOARD_COLS * BOARD_ROWS));
        ptr += BOARD_COLS * BOARD_ROWS;
    }
    size = frame[ptr++];
    players.clear();
    for (int i = 0; i < size; ++i){
        players.insert(frame[ptr], QByteArray(frame.data() + ptr, PLAYER_FRAME_SIZE));
        ptr += PLAYER_FRAME_SIZE;
    }
    if (frame[0] == 2)
    {
        size = frame[ptr++];
        shots.clear();
        for (int i = 0; i < size; ++i){
            shots.insert(frame[ptr], QByteArray(frame.data() + ptr, SHOT_FRAME_SIZE));
            ptr += SHOT_FRAME_SIZE;
        }
    }
}

QByteArray Model::getFrame() const
{
    int n = 3 + BOARD_COLS * BOARD_ROWS + shots.size() * SHOT_FRAME_SIZE + players.size() * PLAYER_FRAME_SIZE;
    int ptr = 0;
    QByteArray frame(n, '\0');
    frame[ptr++] = 2;
    frame.insert(ptr, board.getFrame());
    ptr += BOARD_COLS * BOARD_ROWS;
    frame[ptr++] = players.size();
    foreach (const Player &player, players)
    {
        frame.insert(ptr, player.getFrame());
        ptr += PLAYER_FRAME_SIZE;
    }
    frame[ptr++] = shots.size();
    foreach (const Shot &shot, shots)
    {
        frame.insert(ptr, shot.getFrame());
        ptr += SHOT_FRAME_SIZE;
    }
    frame.resize(n);
    return frame;
}
