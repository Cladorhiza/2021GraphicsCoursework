#include "Entity.h"


Entity::Entity() 
	:x(0), y(0), z(0)
{
}

Entity::Entity(float positionX, float positionY, float positionZ)
	:x(positionX), y(positionY), z(positionZ)
{
}


Entity::~Entity()
{
}
