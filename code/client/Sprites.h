#ifndef SPRITES_H
#define SPRITES_H

#include "../config.h"
#include <QVector>
#include <QPixmap>
#include <QString>


/**
 * @brief
 * Klasa pomocnicza dla Drawera.
 * Przechowuje bitmapy (sprite'y).
 */
class Sprites
{

public:
    Sprites();

    /**
     * @brief
     * Metoda zwraca odpowiedią bitmapę.
     * @param id - nr ID sprite'u - rozpiska w config.h
     * @return - mapa bitowa, czyli nasz sprite
     */
    QPixmap get(int id);

private:
    /**
     * @brief collection Kolekcja przechowująca bitmapy wszystkich sprite'ów
     */
    QVector<QPixmap> collection;

};

#endif // SPRITES_H
