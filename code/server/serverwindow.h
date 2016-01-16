#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include <QCloseEvent>
#include "Server.h"
#include "Data.h"

namespace Ui {
class ServerWindow;
}

/**
 * @brief
 * Główne okno serwera
 */
class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();

private slots:

    /**
     * @brief
     * Slot na akcję naciśnięcia przycisku "Włącz / wyłącz".
     */
    void on_onOffButton_clicked();

    /**
     * @brief
     * Slot do obsługi kliknięcia przycisku "Wybierz mapę".
     */
    void on_selectMapButton_clicked();

    /**
     * @brief
     * Slot do odbioru sygnału zapisanie nowego wpisu do dziennika.
     * @param message - wiadomość
     */
    void server_logged(const QString &message);

    /**
     * @brief
     * Slot odbiera informację o tym, że nowy gracz został dodany.
     * @param player - obiekt gracza
     */
    void server_playerAdded(Player &player);

    /**
     * @brief
     * Slot do przyjęcia sygnału o usunięciu gracza.
     * @param id - nr id gracza
     */
    void server_playerRemoved(int id);

private:

    /**
     * @brief
     * Zdarzenie poprawnie zamyka serwer.
     * @param event - obiekt zdarzenia
     */
    void closeEvent(QCloseEvent *event);

    Ui::ServerWindow *ui;
    Data data;
    Server server;
    bool mapLoaded;

};

#endif // SERVERWINDOW_H
