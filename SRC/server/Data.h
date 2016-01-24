#ifndef DATA_H
#define DATA_H

#include <QMap>
#include "../shared/Model/Model.h"
#include "../shared/PlayerAction.h"

/**
 * @brief
 * Klasa, która przechowuje informacje o grze, czyli:
 * - model
 * - akcje graczy
 */
class Data
{

public:
    Data();

    QMap<int, PlayerAction> playerActions;
    Model model;

};

#endif // DATA_H
