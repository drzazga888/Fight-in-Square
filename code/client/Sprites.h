#ifndef SPRITES_H
#define SPRITES_H

#include "../config.h"
#include <QVector>
#include <QPixmap>
#include <QString>

class Sprites
{

public:
    Sprites();
    QPixmap get(int id);

private:
    QVector<QPixmap> collection;

};

#endif // SPRITES_H
