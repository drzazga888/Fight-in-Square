#ifndef FRAMEAPPLYABLE_H
#define FRAMEAPPLYABLE_H

#include <QByteArray>

class FrameApplyable {

public:
    virtual ~FrameApplyable() {}
    virtual void applyFrame(const QByteArray &frame) = 0;

};

#endif // FRAMEAPPLYABLE_H
