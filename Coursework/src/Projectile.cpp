#include "Projectile.h"



Projectile::Projectile(float width, float height, float positionX, float positionY, float positionZ, float size, bool damaging)
	:Moveable(width, height, positionX, positionY, positionZ, size), damaging(damaging)
{
}

void Projectile::Move(float timeStep) {
	Translate(velocity.x * timeStep, velocity.y * timeStep, 0.0f);
}

Projectile::~Projectile()
{
}
