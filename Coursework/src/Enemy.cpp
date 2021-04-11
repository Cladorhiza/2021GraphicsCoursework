#include "Enemy.h"



Enemy::Enemy(float width, float height, float positionX, float positionY, float positionZ, float size, float speed)
	:Moveable(width, height, positionX, positionY, positionZ, size), speed(speed), alive(true)
{

}



Enemy::~Enemy()
{

}
