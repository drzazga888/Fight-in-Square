#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QPoint>
#include "Data.h"
#include "../config.h"
#include "../shared/Utils/Direction.h"
#include "../shared/Model/BoardElements/ObstacleBoardElement.h"

/**
 * @brief
 * Klasa zarządza logiką aplikacji.
 * Dodaje ona gracza do planszy, potrafi go usunąć,
 * oblicza też nowy stan planszy jeśli upłynie
 * określona ilość czasu.
 */
class Controller
{

public:
    Controller(Data &data);

    /**
     * @brief
     * Metoda dodaje gracza do planszy porzez
     * umieszczenie go w modelu i akcjach graczy.
     * @param id - id gracza
     * @param name - nazwa gracza
     * @return referencja na obiekie Player, który
     * został w metodzie utworzony
     */
    Player &addPlayer(int id, QByteArray name);

    /**
     * @brief
     * Metoda usuwa gracza z plaszy i z akcji graczy.
     * @param id - id gracza do usunięcia
     */
    void removePlayer(int id);

    /**
     * @brief
     * Metoda generuje następny stan planszy, czyli
     * zmienia planszę, graczy i pociski.
     */
    void nextModelStatus();

private:
    Player::GROUP assignGroup();
    DIRECTION assignDirection();
    QPoint assignFreePosition();
    Data &data;

};

#endif // CONTROLLER_H
