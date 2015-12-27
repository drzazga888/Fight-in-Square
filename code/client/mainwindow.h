#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QHostAddress>
#include "../config.h"
#include "canvas.h"
#include "Game.h"
#include "NetworkManager.h"

namespace Ui {
    class MainWindow;
}

/**
 * @brief
 * Główne okno aplikacji
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

public slots:

    /**
     * @brief
     * Slot, który łapie sygnał zmiany stanu aplikacji
     * wysyłany przez klasę Game.
     * Dzięki temu główne okno wie, kiedy przełączyć
     * się na tryb wyświetlania menu/gry,
     * wie kiedy zmienić nazwy przycisków itd...
     * @param gameStatus
     */
    void onGameStatusChanged(Game::STATUS gameStatus);

    /**
     * @brief
     * Slot na sygnał aktualizacji modelu w klasie Game.
     * Gdy odebrany zostanie sygnał, zmienia się np.
     * tabela toplisty, ilość życia gracza itd...
     */
    void onModelActualized();

private slots:

    /**
     * @brief
     * Slot na kliknięcie przycisku "Połącz" bądź
     * "Rozłącz" w menu głównym.
     */
    void on_connectButton_clicked();

    /**
     * @brief
     * Slot na wciśnięcie przycisku "Pomoc"
     * w menu głównym.
     */
    void on_helpButton_clicked();

    /**
     * @brief
     * Slot na wciśnięcie przycisku "Zakończ"
     * w menu głównym.
     */
    void on_exitButton_clicked();

    /**
     * @brief
     * Slot, który obsługuje przycisk
     * rozłączenia się z grą, gdy gracz
     * jest w trakcie gry.
     */
    void on_exitGameButton_clicked();

private:

    /**
     * @brief
     * Obsługa zdarzenia wciśnięcia klawisza.
     * @param e
     * Obiekt zdarzenia
     */
    void keyPressEvent(QKeyEvent *e);

    Ui::MainWindow *ui;
    Game game;
    Canvas canvas;
    NetworkManager networkManager;
    bool updated;

};

#endif // MAINWINDOW_H
