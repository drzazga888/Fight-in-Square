#include "Sprites.h"
#include <QDebug>

Sprites::Sprites()
    :collection(BOARD_FIELDS_LENGTH)
{
    for (int i = 0; i < BOARD_FIELDS_LENGTH; ++i)
        collection[i] = QPixmap(QString(BOARD_FIELD_PATH).arg(i + 1));
}

QPixmap Sprites::get(int id)
{
    if (id != BOARD_FIELD_ID(EMPTY)){
        if (id < 1 || id > BOARD_FIELDS_LENGTH)
            qDebug() << "Błedny indeks sprite'a: " << id;
        else
            return collection[id - 1];
    }
    return QPixmap();
}
