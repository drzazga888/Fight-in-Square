#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QPoint>
#include <QFileDialog>
#include<QtMath>
#include "Data.h"

#include "../config.h"
#include "../shared/Utils/Direction.h"
#include "../shared/Model/BoardElements/ObstacleBoardElement.h"
#define DIRECT(id) data.playerActions[id].moving_direction
#define IS_SHOT(id) data.playerActions[id].player_shooted
#define REGENERATION_TIME 50
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
    void loadExtendedBoard();
private:
    /**
     * @brief extendedBoard Przechowuje informacje o planszy, w tym informacje,
     *  czy dane pole jest zniszczalne, jaki poziom zdrowia ma dane pole.
     * Pierwszy index odpowiada kolumnie, drugi index odpowiada wierszowi.
     */
    QVector<QVector<ObstacleBoardElement> > extendedBoard;  /*!<Pole, które przechowuje planszę z dodatkowymi informacjami: czy pole planszy mozna zniszczyć, ilość życia ma dane pole */
    /**
     * @brief assignGroup Zwraca wartość enumową, która oznacza jedną z dwóch drużyn: RED_GROUP lub BLUE_GROUP
     * @return Player::BLUE_GROUP, jeśli graczy drużyny RED_GROUP więcej,lub
     * Player::RED_GROUP, jeśli graczy drużyny RED_GROUP więcej,lub
     * Player::BLUE_GROUP lub Player::RED_GROUP, jeśli liczba graczy RED_GROUP jest równa liczbie graczy BLUE_GROUP
     */
    Player::GROUP assignGroup();
    /**
     * @brief assignDirection Zwraca wartość enumową, która oznacza jedną z dwóch drużyn:
     * @return
     */
    DIRECTION assignDirection();
    QPoint assignFreePosition();
    Data &data;
    QMap<int,Shot> oldshots;

    QVector<QVector<char> > playerInBoard; /*!<Do debugowania. NIE RUSZAĆ! NIE USUWAĆ*/
    QVector<QVector<char> > shotInBoard; /*!<Do debugowania. NIE RUSZAĆ! NIE USUWAĆ*/
    QVector<QVector<int> > boardInBoard; /*!<Do debugowania. NIE RUSZAĆ! NIE USUWAĆ*/

   private:
    /**
     * @brief movePlayer Metoda
     * @param player    Referencja do obiektu klasy Player, który chcemy przesunąć.
     */
    void movePlayer(Player & player);
    void backmovePlayer(Player & player);
    void SolvePlayerConflict(Player & player1,Player & player2);
    void debugDrawInBoard(QVector<QVector<char> > & playerInBoard, QVector<QVector<char> > &shotInBoard, QVector<QVector<int> > boardInBoard);
    void RefreshPlayerInBoard(QMap<int, Player> futuredPlayers,QVector<QVector<char> > & playerInBoard);
    bool isShotInPlayer(QPoint shot,QPoint player);
    bool isShotInBoard(const QPoint &shot);
    void refreshShotInBoard(const QMap<int,Shot>& futuredShots,QVector<QVector<char> > & shotInBoard);
    void refreshBoardInBoard(QVector<QVector<int> > & boardInBoard);
    int howMuchHurt(int power);
    void SolveFieldsWallAndPlayerConflict(Player & player);
    bool isPlayerInFieldWall(QPoint player,QPoint field);
    bool isFieldsWallAndShotConflict(Shot & shot);
    bool isShotInFieldWall(QPoint shot,QPoint field);
    void givePointsTeam(QMap<int, Player> &players, Player::GROUP grupa, int howPoints);
    int fetchVariablePointsToRange(int i);
    bool isConflictTwoPlayers(QPoint player,QPoint player2 );

public:
    QPoint getActualShotPosition(const Shot & shot) const;
    void loadExtendedBoard(QVector<QVector<int> > idBoard);
    void clearModelFromDataObject();
    static int getNewShotID;
    static int testVariable;


};

#endif // CONTROLLER_H
