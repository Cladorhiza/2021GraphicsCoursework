#include "PatrolEnemy.h"



PatrolEnemy::PatrolEnemy(float width, float height, float positionX, float positionY, float positionZ, float size, float scanRadius, float speed)
	:Enemy(width, height, positionX, positionY, positionZ, size, speed), scanRadius(scanRadius) , patrol1(0.f, 0.f), patrol2(0.f, 0.f), patrolWaypoint(false)
{

}

void PatrolEnemy::Move(float timeStep) {

	Translate(velocity.x * timeStep, velocity.y * timeStep, 0.0f);
}

void PatrolEnemy::Update(float timeStep, Character& c, std::vector<std::vector<int>>& collisionMap) {

	bool attacking = Collision::isCollidingCircle(x, y, scanRadius, c.GetX(), c.GetY(), c.GetSize());

	if (attacking) {
		if (speed < 10.f) speed += 4.f * timeStep;
		velocity = glm::normalize(glm::vec2(c.GetX() - x, c.GetY() - y)) * speed;
	}

	else {

		if (patrolWaypoint) {
			if (Collision::isCollidingCircle(x, y, size, patrol1.x, patrol1.y, 0.5f)) patrolWaypoint = !patrolWaypoint;
			else
				velocity = glm::normalize(glm::vec2(patrol1.x - x, patrol1.y - y)) * speed;
		}
		else {
			if (Collision::isCollidingCircle(x, y, size, patrol2.x, patrol2.y, 0.5f)) patrolWaypoint = !patrolWaypoint;
			else
				velocity = glm::normalize(glm::vec2(patrol2.x - x, patrol2.y - y)) * speed;
		}
	}



	Move(timeStep);
	//if rock hit it
	if (Collision::isCollidingCircle(x, y, size, c.GetRock().GetX(), c.GetRock().GetY(), c.GetRock().GetSize()) && c.GetRock().IsDamaging()) {
		//dead
		alive = false;
		printf("rock");
		c.GetRock().SetDamaging(false);
	}
	//if sword hit it
	if (Collision::isCollidingCircle(x, y, size, c.GetSword().GetX(), c.GetSword().GetY(), c.GetSword().GetSize()) && c.GetSword().IsDamaging()) {
		//dead
		alive = false;
		printf("sword");
	}
	//if collides with player
	if (Collision::isCollidingCircle(x, y, size, c.GetX(), c.GetY(), c.GetSize())) {
		//player dead

	}

	//basic collisions between enemy and terrain
	std::vector<std::pair<int, int>> colls = Collision::GetPotentialRectangleCollidersForCircle(collisionMap, x, y, size);

	for (std::pair<int, int> p : colls) {

		isCollidingRectangle(p.first, p.second);

	}
}

PatrolEnemy::~PatrolEnemy()
{
}
