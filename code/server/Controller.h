#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QPoint>
#include "Data.h"
#include "../config.h"
#include "../shared/Utils/Direction.h"
#include "../shared/Model/BoardElements/ObstacleBoardElement.h"
#define DIRECT(id) data.playerActions[id].moving_direction

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
   // Controller();
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
    QVector<QVector<Player*> > playerInBoard;
   public:
    bool isConflictPlayers(QPoint player1,QPoint player2);
    bool isDoubleConflictPlayers(QPoint player1,QPoint player2);
    void movePlayer(Player & player);
    void backmovePlayer(Player & player);
    void SolvePlayerConflict(Player & player1,Player & player2);
    void DebugDrawPlayerInBoard(QVector<QVector<Player*> > & playerInBoard);
    void RefreshPlayerInBoard(QMap<int, Player> futuredPlayers,QVector<QVector<Player*> > & playerInBoard);



};

#endif // CONTROLLER_H
