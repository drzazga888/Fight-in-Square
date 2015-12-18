#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include "../../config.h"
#include "../Frame/Frameable.h"
#include "Board.h"
#include "Player.h"
#include "Shot.h"

class Model : public Frameable
{

public:
    Model();
    virtual ~Model() {}

    virtual void applyFrame(const QByteArray &frame);
    virtual QByteArray getFrame();

    Board board;
    QVector<Player> players;
    QVector<Shot> shots;

};

#endif // MODEL_H
