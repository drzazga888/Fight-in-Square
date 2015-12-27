#include "Sprites.h"

Sprites::Sprites()
    :collection(BOARD_FIELDS_LENGTH)
{
    for (int i = 0; i < BOARD_FIELDS_LENGTH; ++i)
        collection[i] = QPixmap(QString(BOARD_FIELD_PATH).arg(i + 1));
}

QPixmap Sprites::get(int id)
{
    if (id != BOARD_FIELD_ID(EMPTY))
        return collection[id - 1];
    else
        return QPixmap();
}
