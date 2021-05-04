#include "ThrowingRock.h"


#include "Collision.h"

ThrowingRock::ThrowingRock(float width, float height, float positionX, float positionY, float positionZ, float size, bool damaging, bool bouncy, bool rotates, float lifeTime)
	:Projectile(width, height, positionX, positionY, positionZ, size, damaging, bouncy), lifeTime(lifeTime), rotates(rotates), currentLifeTime(lifeTime)
{
	
}

void ThrowingRock::Move(float timeStep) {

	

	Translate(velocity.x * timeStep, velocity.y * timeStep, 0.0f);
}

void ThrowingRock::Update(float timeStep, std::vector<std::vector<int>>& collisionMap, irrklang::ISoundEngine* soundEngine) {
	
	
	currentLifeTime -= timeStep;
	Move(timeStep);
	if (rotates) rotation += 3.1415f * 2 * timeStep;
	if (currentLifeTime < 0.f) {
		//reset
		damaging = false;
		currentLifeTime = lifeTime;
	}
	
	//check collisions with surrounding tiles
	std::vector<std::pair<int, int>> colls = Collision::GetPotentialRectangleCollidersForCircle(collisionMap, x, y, size);

	for (std::pair<int, int> p : colls) {

		if (isCollidingRectangle(p.first, p.second)) {
			soundEngine->play2D("../res/audio/rock bounce.mp3");

			if (!bouncy) 
				currentLifeTime = lifeTime;
		}

	}
}

void ThrowingRock::Reset(float x, float y, float z, glm::vec2 velocity) {

	currentLifeTime = lifeTime;
	SetPosition(x, y, z);
	SetVelocity(velocity);
	SetDamaging(true);
}

ThrowingRock::~ThrowingRock()
{
}
