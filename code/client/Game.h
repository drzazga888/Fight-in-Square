#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QTime>
#include <QElapsedTimer>
#include "../config.h"
#include "../shared/Utils/Direction.h"
#include "../shared/PlayerAction.h"
#include "../shared/Model/Model.h"

/**
 * @brief
 * Główna klasa, która zawiera wszystkie informacje
 * o grze takie jak:
 * - stan gry
 * - 2 obiekty typu Model: model1 (poprzedni stan)
 *   i model2 (następny) - potrzebne są 2 bo można
 *   dzięki robić płynne przejścia pomiędzy stanami (modelami)
 * - funkcje, która zwraca współczynnik nałożenia
 *   jednego modelu na drugi, wartości od 0 do 1, może
 *   się zdarzyć, że będzie wartość większa niż 1
 * - akcje grającego - tzn czy został wykonany ruch,
 *   kierunek tego ruchu i czy gracz wystrzelił pocisk
 */
class Game: public QObject, public FrameApplyable
{
    Q_OBJECT

public:

    /**
     * @brief Stany gry
     */
    enum STATUS {
        NO_PLAYING,
        CONNECTING,
        SENDING_HELLO,
        WAITING_FOR_PLAYER,
        PLAYING,
        SENDING_GOODBYE,
        DISCONNECTING
    };

    Game();

    /**
     * @brief
     * Funkcja sprawdza, czy wciśnięty klawisz
     * nie jest czasami akcją gracza, którą
     * trzeba przechwycić
     * @param key
     * Kod klawisza
     */
    void handleKeyPress(int key);

    /**
     * @brief
     * Funkcja sprawdza, czy wciśnięty puszczony
     * nie jest czasami akcją gracza, którą
     * trzeba przechwycić
     * @param key
     * Kod klawisza
     */
    void handleKeyRelease(int key);

    /**
     * @brief
     * Metoda zwraca współczynnik nałożenia się
     * jednego modelu na drugi
     * @return
     * Wartość od 0 do 1. Czasami ta wartość
     * może być większa niż 1 - wtedy należy
     * to traktować jako 1.
     */
    float getPhaseOverlay();

    /**
     * @brief
     * Funkcja ustawia stan gry.
     * Po ustawieniu wysyłany jest odpowiedni sygnał.
     * @param status stan gry
     */
    void setStatus(STATUS status);

    /**
     * @brief setErrorCode
     * @param errCode kod błędu
     */
    void setErrorCode(int errCode);

    /**
     * @brief
     * Metoda odziedziczona bo klasie abstrakcyjnej
     * FrameApplyable. Dzięki temu
     * klasa może na podstawie ramki
     * ustawić w odpowiedni sposób swój stan.
     * @param frame
     * Ramka typu QByteArray
     */
    void applyFrame(const QByteArray &frame);

    STATUS status;
    int errCode;
    Model model1, model2;
    PlayerAction player;
    QElapsedTimer frameUpdateTimer;
    QTime gameTime;
    QString playerName;
    QTime maxTime;

signals:

    /**
     * @brief
     * Sygnał wysyłany, gdy stan aplikacji ulegnie zmianie,
     * czyli gdy zostanie wywołana metoda setStatus
     * @param status stan gry
     * @param errCode kod błędu
     */
    void gameStatusChanged(Game::STATUS gameStatus);

    /**
     * @brief errorCodeChanged
     * @param errCode kod błędu
     */
    void errorCodeChanged(int errCode);

    /**
     * @brief
     * Sygnał, który jest emitowany, gdy model został
     * zaktualizowany - dzięki temu np. główne okno
     * wie o tym, by przerysować interfejs.
     */
    void modelActualized();

private:
    int frameToFrameElapsed;

};

#endif
