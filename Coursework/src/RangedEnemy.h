#pragma once
#include "Enemy.h"
#include "Collision.h"
#include "irrKlang.h"
class RangedEnemy :
	public Enemy
{
protected:
	float scanRadius;
	Texture bullet;
	std::vector<std::unique_ptr<ThrowingRock>> gunFire;
	int currentBullet;
	float bulletCooldown;
	float currentBulletCooldown;
public:
	RangedEnemy(float width, float height, float positionX, float positionY, float positionZ, float size, float scanRadius, float speed);
	void Move(float timeStep);
	void Update(float timeStep, Character& c, std::vector<std::vector<int>>& collisionMap, irrklang::ISoundEngine* soundEngine);
	void Init(float colour[3], Texture* texture);
	inline std::vector<std::unique_ptr<ThrowingRock>>& getBullets() { return gunFire; }
	~RangedEnemy();
	RangedEnemy(RangedEnemy&& other);
};

