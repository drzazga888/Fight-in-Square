#ifndef FRAMEGIVEABLE_H
#define FRAMEGIVEABLE_H

#include <QByteArray>

class FrameGiveable {

public:
    virtual ~FrameGiveable() {}
    virtual QByteArray getFrame() = 0;

};

#endif // FRAMEGIVEABLE_H
