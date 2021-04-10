#include "ThrowingRock.h"


#include "Collision.h"

ThrowingRock::ThrowingRock(float width, float height, float positionX, float positionY, float positionZ, float size, bool damaging, bool bouncy)
	:Projectile(width, height, positionX, positionY, positionZ, size, damaging, bouncy), lifeTime(3.f)
{
}

void ThrowingRock::Move(float timeStep) {

	

	Translate(velocity.x * timeStep, velocity.y * timeStep, 0.0f);
}

void ThrowingRock::Update(float timeStep, std::vector<std::vector<int>>& collisionMap) {

	lifeTime -= timeStep;
	Move(timeStep);
	rotation += 0.01f;
	if (lifeTime < 0.f) {
		damaging = false;
		lifeTime = 3.f;
	}
	
	std::vector<std::pair<int, int>> colls = Collision::GetPotentialRectangleCollidersForCircle(collisionMap, x, y, size);

	for (std::pair<int, int> p : colls) {

		isCollidingRectangle(p.first, p.second);

	}
}

ThrowingRock::~ThrowingRock()
{
}
