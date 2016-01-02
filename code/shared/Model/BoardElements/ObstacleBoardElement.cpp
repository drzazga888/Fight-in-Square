#include "ObstacleBoardElement.h"

ObstacleBoardElement::ObstacleBoardElement():BoardElement(0), isDestructable(false), health(0){

}

ObstacleBoardElement::ObstacleBoardElement(int id, bool isDestructable, int health)
:BoardElement(id), isDestructable(isDestructable), health(health)
{
}
