#ifndef FRAMEAPPLYABLE_H
#define FRAMEAPPLYABLE_H

#include <QByteArray>

/**
 * @brief
 * Klasa abstrakcyjna, która narzuca
 * utworzenie metody, która przyjmuje ramkę
 * jako parametr i aplikuje ją na obiekcie.
 */
class FrameApplyable {

public:
    virtual ~FrameApplyable() {}

    /**
     * @brief
     * Metoda aplikuje / przetwarza ramkę na obiekcie.
     * @param frame - ramka
     */
    virtual void applyFrame(const QByteArray &frame) = 0;

};

#endif // FRAMEAPPLYABLE_H
