#ifndef LOADER_H
#define LOADER_H
#include"config.h"
#include<QString>
#include<QDebug>
#include<QFileDialog>
#include<QFileInfo>
#include<QVector>


/**
 * @brief The Loader class
 * Klasa wczytująca id elementów planszy z pliku.
 * Przechowuje je.
 */
class Loader
{
public:
    /**
     * @brief Loader
     * Konstruktor domyślny.
     * Inicjalizuje filePathName pustym QStringiem.
     * Inicjalizuje idBoard wartościami 0.
     */
    Loader();
    /**
     * @brief Loader
     * Konstruktor jednoparametrowy.
     * Inicjalizuje idBoard wartościami 0.
     * @param fileName ścieżka do pliku mapowego.
     * Jeśli pliku ze ścieżki nie ma albo plik ze ścieżki nie ma rozszerzenia .map,
     * wówczas pole filePathName inicjalizowane pustym QStringiem
     */
    Loader(QString fileName);
    /**
     * @brief loadIDMapFromFile
     *  Metoda wpisuje do idBoard dane z pliku mapowego(jeśli plik mapowy jest odpowiedni),
     * do którego ścieżka znajduje się w polu filePathName
     * Jeśli filePathName puste, wówczas idBoard zainicjalizowane zeerami
     * @return false jeśli pole filePathName jest puste
     * true jeśli pole filePathName nie jest puste
     */
    bool loadIDMapFromFile();
    /**
     * @brief SetFilePathName
     * Metoda pozwala zmienić wartość pola filePathName
     * Jeśli pliku ze ścieżki nie ma albo plik ze ścieżki nie ma rozszerzenia .map,
     * wówczas pole filePathName inicjalizowane pustym QStringiem
     * @param name ścieżka do pliku mapowego z rozszerzeniem .map
     * @return false jeśli pole filePathName jest puste
     * true jeśli pole filePathName nie jest puste
     */
    bool SetFilePathName(QString name);
    /**
     * @brief SetFilePathName
     * Metoda pozwala zmienić wartość pola filePathName przy pomocy okna dialogowego
     * Jeśli nie wybierzemy żadnego pliku,
     * wówczas pole filePathName nie zostanie zmienione
     * @return (*this)
     */
    Loader & SetFilePathName();
    const QVector<QVector<int> > & getIdBoard();

private:
    /**
     * @brief filePathName
     * Zawiera ścieżkę do pliku mapowego
     */
    QString filePathName;
    /**
     * @brief idBoard
     * Tablica przechowująca wartości id pól
     */
    QVector<QVector<int> > idBoard;
};

#endif // LOADER_H
