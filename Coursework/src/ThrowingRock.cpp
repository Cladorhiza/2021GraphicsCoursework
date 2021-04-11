#include "ThrowingRock.h"


#include "Collision.h"

ThrowingRock::ThrowingRock(float width, float height, float positionX, float positionY, float positionZ, float size, bool damaging, bool bouncy, bool rotates, float lifeTime)
	:Projectile(width, height, positionX, positionY, positionZ, size, damaging, bouncy), lifeTime(lifeTime), rotates(rotates), currentLifeTime(lifeTime)
{
	
}

void ThrowingRock::Move(float timeStep) {

	

	Translate(velocity.x * timeStep, velocity.y * timeStep, 0.0f);
}

void ThrowingRock::Update(float timeStep, std::vector<std::vector<int>>& collisionMap) {

	currentLifeTime -= timeStep;
	Move(timeStep);
	if (rotates) rotation += 3.1415f * 2 * timeStep;
	if (currentLifeTime < 0.f) {
		damaging = false;
		currentLifeTime = lifeTime;
	}
	
	std::vector<std::pair<int, int>> colls = Collision::GetPotentialRectangleCollidersForCircle(collisionMap, x, y, size);

	for (std::pair<int, int> p : colls) {

		if (isCollidingRectangle(p.first, p.second)) {
			if (!bouncy) 
				currentLifeTime = lifeTime;
		}

	}
}

ThrowingRock::~ThrowingRock()
{
}
