#include "ObstacleBoardElement.h"

ObstacleBoardElement::ObstacleBoardElement(int id, bool isDestructable, int health)
:BoardElement(id), isDestructable(isDestructable), health(health)
{
}
