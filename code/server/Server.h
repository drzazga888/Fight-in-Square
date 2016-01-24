#ifndef SERVER_H
#define SERVER_H

#include <cstdlib>
#include <QObject>
#include <QString>
#include <QDateTime>
#include <QElapsedTimer>
#include "../config.h"
#include "Data.h"
#include "TcpServer.h"
#include "Controller.h"
#include "loader.h"
#include "../shared/Model/Player.h"
#include <QByteArray>

/**
 * @brief
 * Główna klasa zarządzająca wszystkim.
 * Zawiera tcpServer, który jest
 * odpowiedzialny za komunikację z klientami.
 * Klasa potrafi wysłać ramki i je odbrać, a potem
 * odpowiednio obrobić i przekazać.
 * Klasa jest sterowana przez główny timer i sygnały
 * od serwera.
 */
class Server: public QObject
{
    Q_OBJECT

public:
    explicit Server(Data &data, QObject *parent = 0);
    ~Server();

    /**
     * @brief
     * Metoda, którą należy wywołać, jeśli chcemy
     * zachować informację o tym, co się stało w
     * danej chwili.
     * @param message - wiadomość tego, co się stało
     */
    void log(const QString &message);

    /**
     * @brief
     * Metoda włącza serwer
     * @param port - numer portu, który będzie nasłuchiwany
     * @return informacja, czy włączanie przebiegło pomyślnie:
     * true - wszystko ok
     * false - błąd
     */
    bool switchOn(int port, const QTime &maxTime);

    /**
     * @brief
     * Metoda wyłącza serwer.
     * @return informacja, czy wyłączanie przebiegło pomyślnie:
     * true - wszystko ok
     * false - błąd
     */
    bool switchOff();

    /**
     * @brief startPlaying
     * Jeśli conajmniej dwóch graczy się połączy,
     * to serwer może zacząć rozsyłać planszę i naliczać
     * czas gry.
     * To jest funkcja, która wykonuje tą akcję,
     * jest ona niezależna względem switchOn,
     * bo wspomniana metoda włącza serwer i
     * pozwala tylko połączyć się z serwerem.
     */
    void startPlaying();

    bool isWorking;
    /**
     * @brief refreshController Pobiera mapę do serwera,
     * czyści kontroler oraz pobiera mapę do kontrolera
     */
    void refreshController();
    /**
     * @brief setPathExtendedMap Ustawia ścieżkę do pliku z mapą
     * @param load  Ścieżka do pliku z mapą
     */
    void setPathExtendedMap(QString &load);

public slots:

    /**
     * @brief
     * Slot do czytania ramki, która przyszła od klienta.
     * @param playerId - nr id gracza
     * @param message - wiadomość jako ramka
     */
    void read(int playerId, const QByteArray &message);

    /**
     * @brief
     * Slot do obsługi rozłączenia się któregoś z klientów.
     * @param playerId - nr id gracza
     */
    void disconnected(int playerId);
signals:

    /**
     * @brief
     * Sygnał emitowany, gdy serwer otrzyma wiadomość.
     * @param message - wiadomość, która dalej jest przekazywana
     */
    void logged(const QString &message);

    /**
     * @brief
     * Sygnał emitowany, gdy nowy gracz zostanie dodany.
     * @param player - obiekt gracza
     */
    void playerAdded(Player &player);

    /**
     * @brief
     * Sygnał emitowany, gdy gracz zostanie usunięty.
     * @param id - nr id gracza
     */
    void playerRemoved(int id);

    /**
     * @brief serverClosed
     * Sygnał emitowany, gdy serwer zostanie wyłączony
     */
    void serverClosed();

private:

    /**
     * @brief
     * Zdarzenie czasowe, które informuje serwer,
     * że należy wykonać cykliczną akcję np. obliczenie
     * nowego stanu ramek i wysłanie go graczom.
     */
    void timerEvent(QTimerEvent *);

    bool isNameUnique(QString name);

    Loader mapFromFile;
    Data &data;
    TcpServer tcpServer;
    Controller controller;
    QElapsedTimer gameTime;
    int timerId;
    bool isTimerRunning;
    int port;
    QTime maxTime;

};

#endif // SERVER_H
