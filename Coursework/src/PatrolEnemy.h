#pragma once
#include "Enemy.h"
#include "Collision.h"
#include "irrKlang.h"
class PatrolEnemy :
	public Enemy
{
protected:
	float scanRadius;
	glm::vec2 patrol1;
	glm::vec2 patrol2;
	bool patrolWaypoint;

public:
	PatrolEnemy(float width, float height, float positionX, float positionY, float positionZ, float size, float scanRadius, float speed);
	void Move(float timeStep);
	void Update(float timeStep, Character& c, std::vector<std::vector<int>>& collisionMap, irrklang::ISoundEngine* soundEngine);
	inline void setPatrols(glm::vec2 pat1, glm::vec2 pat2) { patrol1 = pat1; patrol2 = pat2; }
	~PatrolEnemy();
};

