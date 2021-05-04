#pragma once
#include "Projectile.h"
#include "irrKlang.h"
class ThrowingRock : public Projectile
{
protected:
	float lifeTime;
	float currentLifeTime;
	bool rotates;
public:
	ThrowingRock(float width, float height, float positionX, float positionY, float positionZ, float size, bool damaging, bool bouncy, bool rotates, float lifeTime);
	~ThrowingRock();
	void Move(float timeStep);
	void Update(float timeStep, std::vector<std::vector<int>>& collisionMap, irrklang::ISoundEngine* soundEngine);
	inline void setLifeTime(int lifeTime) { currentLifeTime = lifeTime; }
	void Reset(float x, float y, float z, glm::vec2 velocity);
};

