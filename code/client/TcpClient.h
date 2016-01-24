#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>

/**
 * @brief The TcpClient class
 * Klasa odpowiedzialna za obsługę połączenia i przesyłanie danych przez sieć
 */
class TcpClient : public QWidget
{
	Q_OBJECT
public:
    /**
     * @brief TcpClient
     * Konstruktor inicjujący nieaktywne połączenie
     */
	TcpClient();

	~TcpClient();
    /**
     * @brief connectToHost Funkcja łącząca się z hostem o podanym adresie IP i numerze portu
     * @param address adres IP hosta
     * @param port numer portu
     */
	void connectToHost(QHostAddress address, int port);

    /**
     * @brief disconnectFromHost Metoda zamykająca połączenie TCP
     */
	void disconnectFromHost();
public slots:
    /**
     * @brief read Slot, który jest wywoływany jeżeli przyjdą jakieś dane z serwera
     */
    void read();

    /**
     * @brief write Slot, który jest wywoływany, jesli jakieś dane maja zostać przesłane do serwera
     * @param message przesyłane dane
     */
	void write(QByteArray message);

    /**
     * @brief onConnected Slot, który jest wywoływany w momencie połączenia się z serwerem.
     * Ustawia połączenie jako otwarte.
     */
    void onConnected();

    /**
     * @brief onDisconnected Slot, który jest wywoływany w momencie rozłączenia się z serwerem.
     * Ustawia połączenie jako zamknięte.
     */
    void onDisconnected();
signals:
    /**
     * @brief connecting Sygnał zgłaszany w momencie połączenia się z serwerem
     */
	void connecting();

    /**
     * @brief disconnecting Sygnał zgłaszany w momencie rozłączenia się z serwerem
     */
	void disconnecting();

    /**
     * @brief reading Sygnał zgłaszany w momencie, kiedy jakieś dane zostaną przysłane.
     * Przekazuje te dane do obsługującego go slotu.
     */
	void reading(QByteArray);

    /**
     * @brief writing Sygnał zgłaszany w momencie, kiedy jakieś dane zostaną wysłane.
     * Przekazuje te dane do obsługującego go slotu.
     */
	void writing(QByteArray);
private:
    /**
     * @brief socket Obiekt gniazda sieciowego, reprezentującego połączenie
     */
	QTcpSocket* socket;

    /**
     * @brief connected Flaga informująca o tym, czy połączenie jest otwarte
     */
	bool connected;
};

#endif
