#ifndef FRAMEGIVEABLE_H
#define FRAMEGIVEABLE_H

#include <QByteArray>

/**
 * @brief
 * Klasa narzuca implementację metody, która
 * produkuje ramkę na podstawie obiektu.
 */
class FrameGiveable {

public:
    virtual ~FrameGiveable() {}

    /**
     * @brief
     * Produkuje ramkę.
     * @return ramka
     */
    virtual QByteArray getFrame() const = 0;

};

#endif // FRAMEGIVEABLE_H
