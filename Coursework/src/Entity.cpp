#include "Entity.h"


Entity::Entity() 
	:x(0), y(0), z(0), rotation(0)
{
}

Entity::Entity(float positionX, float positionY, float positionZ)
	:x(positionX), y(positionY), z(positionZ), rotation(0)
{
}


Entity::~Entity()
{
}
