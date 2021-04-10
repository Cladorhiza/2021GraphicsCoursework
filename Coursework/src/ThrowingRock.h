#pragma once
#include "Projectile.h"
class ThrowingRock : public Projectile
{
protected:
	float lifeTime;
public:
	ThrowingRock(float width, float height, float positionX, float positionY, float positionZ, float size, bool damaging, bool bouncy);
	~ThrowingRock();
	void Move(float timeStep);
	void Update(float timeStep, std::vector<std::vector<int>>& collisionMap);
};

