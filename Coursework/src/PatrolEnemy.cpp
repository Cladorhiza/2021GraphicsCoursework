#include "PatrolEnemy.h"



PatrolEnemy::PatrolEnemy(float width, float height, float positionX, float positionY, float positionZ, float size, float scanRadius, float speed)
	:Enemy(width, height, positionX, positionY, positionZ, size, speed), scanRadius(scanRadius) , patrol1(0.f, 0.f), patrol2(0.f, 0.f), patrolWaypoint(false)
{

}

void PatrolEnemy::Move(float timeStep) {

	Translate(velocity.x * timeStep, velocity.y * timeStep, 0.0f);
}

void PatrolEnemy::Update(float timeStep, Character& c, std::vector<std::vector<int>>& collisionMap, irrklang::ISoundEngine* soundEngine) {

	//check if character colliding with circle of radius scanrange
	bool attacking = Collision::IsCollidingCircle(x, y, scanRadius, c.GetX(), c.GetY(), c.GetSize());

	if (attacking) {
		//increase speed and set velocity towards the character
		if (speed < 10.f) speed += 4.f * timeStep;
		velocity = glm::normalize(glm::vec2(c.GetX() - x, c.GetY() - y)) * speed;
	}

	else {
		//patrol between preset patrol points
		if (patrolWaypoint) {
			if (Collision::IsCollidingCircle(x, y, size, patrol1.x, patrol1.y, 0.05f)) patrolWaypoint = !patrolWaypoint;
			else
				velocity = glm::normalize(glm::vec2(patrol1.x - x, patrol1.y - y)) * speed;
		}
		else {
			if (Collision::IsCollidingCircle(x, y, size, patrol2.x, patrol2.y, 0.05f)) patrolWaypoint = !patrolWaypoint;
			else
				velocity = glm::normalize(glm::vec2(patrol2.x - x, patrol2.y - y)) * speed;
		}
	}



	Move(timeStep);
	//if rock hit it
	if (Collision::IsCollidingCircle(x, y, size, c.GetRock().GetX(), c.GetRock().GetY(), c.GetRock().GetSize()) && c.GetRock().IsDamaging()) {
		//dead
		soundEngine->play2D("../res/audio/rock hit.mp3");
		alive = false;
		printf("rock");
		c.GetRock().SetDamaging(false);
	}
	//if sword hit it
	if (Collision::IsCollidingCircle(x, y, size, c.GetSword().GetX(), c.GetSword().GetY(), c.GetSword().GetSize()) && c.GetSword().IsDamaging()) {
		//dead
		soundEngine->play2D("../res/audio/sword hit.mp3");
		alive = false;
		printf("sword");
	}
	//if collides with player
	if (Collision::IsCollidingCircle(x, y, size, c.GetX(), c.GetY(), c.GetSize())) {
		//player dead
		c.SetAlive(false);
		soundEngine->play2D("../res/audio/rock hit.mp3");
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
