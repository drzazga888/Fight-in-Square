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
    /**
     * @brief
     * Metoda dodaje gracza do planszy porzez
     * umieszczenie go w modelu i akcjach graczy.
     * @param id - id gracza
     * @param player - gracz
     * @return referencja na obiekie Player, który
     * został w metodzie utworzony
     */
    Player &addPlayer(int id, Player player);
private:
    /**
     * @brief extendedBoard Przechowuje informacje o planszy, w tym informacje,
     *  czy dane pole jest zniszczalne, jaki poziom zdrowia ma dane pole.
     * Pierwszy index odpowiada kolumnie, drugi index odpowiada wierszowi.
     */
    QVector<QVector<ObstacleBoardElement> > extendedBoard;
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
    /**
     * @brief assignFreePosition Zwraca nowe wpółrzędne położenia środka gracza(gęstsze), które sa wolne.
     * @return Nowe wpółrzędne położenia środka gracza(gęstsze), które sa wolne.
     */
    QPoint assignFreePosition();
    /**
     * @brief data Przechowuje dane na temat graczy, pocisków, planszy, akcji graczy.
     */
    Data &data;
    /**
     * @brief oldshots Kontener zawierający informacje o pociskach z poprzedniego cyklu obliczeniowego serwera
     */
    QMap<int,Shot> oldshots;
    /**
     * @brief playerInBoard Tablica dwuwymiarowa char'ów, która ilustruje położenie graczy na planszy
     */
    QVector<QVector<char> > playerInBoard;
    /**
     * @brief shotInBoard Tablica dwuwymiarowa char'ów, która ilustruje położenie pocisków na planszy
     */
    QVector<QVector<char> > shotInBoard; /*!<Do debugowania. NIE RUSZAĆ! NIE USUWAĆ*/
    /**
     * @brief boardInBoard Tablica dwuwymiarowa int'ów, która ilustruje obraz samej planszy
     */
    QVector<QVector<int> > boardInBoard; /*!<Do debugowania. NIE RUSZAĆ! NIE USUWAĆ*/

   private:
    /**
     * @brief movePlayer Przesuwa gracza na podstawie informacji o akcji gracza z obiektu . Korzysta z obiektu QMap<int, PlayerAction>.
     * Gracz nie zostanie przesuniety, jesli będzie chciał wyjść poza obszar planszy.
     * @param player    Gracz, którego chcemy przesunąć.
     */
    void movePlayer(Player & player);
    /**
     * @brief backmovePlayer Cofa  gracza, jeśli gracz wykonał ruch i jeszcze nie został cofnięty
     * w danym cyklu obliczeń serwera .
     * @param player Gracz, którego chcemy cofnąć.
     */
    void backmovePlayer(Player & player);
    /**
     * @brief SolvePlayerConflict Wykrywa, czy dwóch graczy się na siebie nakłada.
     * Jeśli tak, wówczas jeden lub dwóch graczy jest cofanych. Gracz może zostać cofnięty, jeśli
     * wykonał ruch i jeszcze nie został cofnięty w danym cyklu obliczen serwera
     * @param player1 Gracz, dla którego badamy konflikt z player2
     * @param player2 Gracz, dla którego badamy konflikt z player1
     */
public:
    void SolvePlayerConflict(Player & player1,Player & player2);
    /**
     * @brief debugDrawInBoard  Wyświetla grę w postaci "literowo-cyferkowej" na konsoli qDebug'a
     * @param playerInBoard Tablica dwuwymiarowa char'ów, która ilustruje położenie graczy na planszy
     * @param shotInBoard Tablica dwuwymiarowa char'ów, która ilustruje położenie pocisków na planszy
     * @param boardInBoard Tablica dwuwymiarowa int'ów, która ilustruje obraz samej planszy
     */
public:
    void debugDrawInBoard(QVector<QVector<char> > & playerInBoard, QVector<QVector<char> > &shotInBoard, QVector<QVector<int> > boardInBoard);
    /**
     * @brief RefreshPlayerInBoard Odświeża tablicę dwuwymiarowa char'ów,
     * która ilustruje położenie graczy na planszy.
     * @param futuredPlayers Zawiera informacje na temat graczy.
     * @param playerInBoard Tablica dwuwymiarowa char'ów, która ilustruje położenie graczy na planszy
     */
    void RefreshPlayerInBoard(QMap<int, Player> futuredPlayers,QVector<QVector<char> > & playerInBoard);
    /**
     * @brief isShotInPlayer Sprawdza, czy gracz został trafiony pociskiem
     * @param shot  Współrzędne aktualnego położenia pocisku
     * @param player Współrzędne położenia środka gracza
     * @return  true, jeśli gracz został trafiony pociskiem,
     * false, jeśli gracz nie został trafiony pociskiem
     */
    bool isShotInPlayer(QPoint shot,QPoint player);
    /**
     * @brief isShotInBoard Sprawdza, czy pocisk znajduje się na planszy
     * @param shot  Pocisk
     * @return true, jeśli pocisk jest na planszy,
     * false, jeśli pocisk wyszedł poza obszar planszy
     */
    bool isShotInBoard(const QPoint &shot);
    /**
     * @brief refreshShotInBoard Odświeża tablicę dwuwymiarowa char'ów,
     * która ilustruje położenie graczy na planszy.
     * @param futuredShots Zawiera informacje na temat pocisków.
     * @param shotInBoard Tablica dwuwymiarowa char'ów, która ilustruje położenie pocisków na planszy
     */
    void refreshShotInBoard(const QMap<int,Shot>& futuredShots,QVector<QVector<char> > & shotInBoard);
    /**
     * @brief refreshBoardInBoard  Odświeża tablicę dwuwymiarowa int'ów,
     * która ilustruje obraz samej planszy
     * @param boardInBoard Tablica dwuwymiarowa int'ów, która ilustruje obraz samej planszy
     */
    void refreshBoardInBoard(QVector<QVector<int> > & boardInBoard);
     public:
    /**
     * @brief howMuchHurt Zwraca wartość obrażeń w zależności od danego parametru mocy gracza
     * @param power Wartość mocy
     * @return wartość obrażeń
     */

    int howMuchHurt(int power);
private:
    /**
     * @brief SolveFieldsWallAndPlayerConflict Wykrywa,
     * czy dwóch gracz wszedł na ścianę lub wyszedł za planszę.
     * Jeśli tak, wówczas jeden lub dwóch graczy jest cofanych. Gracz może zostać cofnięty, jeśli
     * wykonał ruch i jeszcze nie został cofnięty w danym cyklu obliczen serwera
     * @param player Gracz, dla którego badamy konflikt
     */
    void SolveFieldsWallAndPlayerConflict(Player & player);
    /**
     * @brief isPlayerInFieldWall  Wykrywa,
     * czy gracz pokrywa się z polem planszy, na które gracz nie może wejść.
     * @param player Współrzędne aktualnego położenia gracza (współrzędne gęstsze)
     * @param field Współrzędne położenia środka gracza (współrzędne rzadsze)
     * @return true, jeśli gracz pokrywa się z polem planszy, na które gracz nie może wejść,
     * false, jesli gracz nie pokrywa się z polem planszy, na które gracz nie może wejść.
     */
    bool isPlayerInFieldWall(QPoint player,QPoint field);
    /**
     * @brief isFieldsWallAndShotConflict Sprawdza, czy jest konflikt między pociskiem
     *  a polem plaszy, przez który pocisk nie może przelecieć.Jeśli jest konflikt, Modyfikuje poziom życia pól,
     *  które posiadają punkty życia i zmienia takie pola na inne pole, jeśli
     * przyszły poziom życia jest niedodatni.
     * @param shot Pocisk
     * @return true, jeśli jest konflikt,
     * false, jeśli nie ma konfliktu
     */
    bool isFieldsWallAndShotConflict(Shot & shot);
    /**
     * @brief isShotInFieldWall Sprawdza, czy pocisk trafił w pole, przez które nie może przelecieć
     * @param shot Współrzędne pocisku (gęstsze)
     * @param field Współrzedne pola planszowego (rzadsze)
     * @return true, jeśli pocisk trafił w pole, przez które nie może przelecieć
     * false, jeśli pocisk nie trafil w pole, przez które pocisk nie może preecieć
     */
    bool isShotInFieldWall(QPoint shot,QPoint field);
    /**
     * @brief givePointsTeam Przydziela danej drużynie punkty
     * @param players Kontener ze wszystkimi graczami
     * @param grupa Grupa, której gracze mają dostać punkty
     * @param howPoints liczba przyznanych punktów
     */
    void givePointsTeam(QMap<int, Player> &players, Player::GROUP grupa, int howPoints);
    /**
     * @brief fetchVariablePointsToRange Sprowadza liczbę do zakresu z przedziału [0;255]
     * @param i Liczba
     * @return Taką samą liczbę, jeśli parametr i należy do przedziału [0;255],
     * 0, jeśli parametr jest mniejszy od 0,
     * 255, jeśli parametr jest większy od 255.
     */
    int fetchVariablePointsToRange(int i);
    /**
     * @brief isConflictTwoPlayers Wykrywa, czy dwóch graczy się na siebie nakłada.
     * @param player Współrzędne środka połozenia jednego gracza
     * @param player2 Współrzędne srodka położenia drugiego gracza
     * @return true, jeśli dwóch się nakładają,
     * false jeśli jeśli sie nie nakładają
     */
    bool isConflictTwoPlayers(QPoint player,QPoint player2 );

public:
    /**
     * @brief getActualShotPosition Zwraca aktualne współrzędne połozenia lecącego pocisku
     * @param shot Pocisk
     * @return Aktualne wspołrzedne położenia lecącego pocisku
     */
    QPoint getActualShotPosition(const Shot & shot) const;
    /**
     * @brief loadExtendedBoard Wczutuje mape do kontrolera
     * @param idBoard Tablica dwowymiarowa z id pól
     */
    void loadExtendedBoard(QVector<QVector<int> > idBoard);
    /**
     * @brief clearModelFromDataObject Nadpisuje stary model pustym modelem
     */
    void clearModelFromDataObject();
    /**
     * @brief getNewShotID Używana m.in. do nadawania pociskom id
     */
    static int getNewShotID;
   // static int testVariable;


};

#endif // CONTROLLER_H
