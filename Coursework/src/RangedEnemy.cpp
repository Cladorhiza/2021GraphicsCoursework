#include "RangedEnemy.h"
#include "not_my_code/glm/gtx/rotate_vector.hpp"
#include <iostream>


RangedEnemy::RangedEnemy(float width, float height, float positionX, float positionY, float positionZ, float size, float scanRadius, float speed)
	:Enemy(width, height, positionX, positionY, positionZ, size, speed), scanRadius(scanRadius), currentBullet(0), bulletCooldown(0.2f), currentBulletCooldown(0.f)
{

}

void RangedEnemy::Move(float timeStep) {

	Translate(velocity.x * timeStep, velocity.y * timeStep, 0.0f);
}

void RangedEnemy::Update(float timeStep, Character& c, std::vector<std::vector<int>>& collisionMap) {

	bool attacking = Collision::isCollidingCircle(x, y, scanRadius, c.GetX(), c.GetY(), c.GetSize());

	if (attacking) {
		
		glm::vec2 vecToCharacter(c.GetX() - x, c.GetY() - y);
		glm::vec2 directionFacing(0.f,1.f);
		
		float dotProduct = glm::dot(directionFacing, vecToCharacter);

		float angleToRotate = glm::acos(dotProduct / (glm::length(directionFacing) * glm::length(vecToCharacter)));

		if (directionFacing.x * vecToCharacter.y + directionFacing.y * vecToCharacter.x > 0.f) {
			rotation = angleToRotate;
		}
		else
			rotation = -angleToRotate;

		currentBulletCooldown += timeStep;
		if (currentBulletCooldown > bulletCooldown) {

			if (!gunFire[currentBullet]->IsDamaging()) {

				gunFire[currentBullet]->SetPosition(x, y, z);
				gunFire[currentBullet]->SetVelocity(glm::rotate(directionFacing, -rotation) * 10.f);
				gunFire[currentBullet]->SetDamaging(true);
				gunFire[currentBullet]->SetRotation(rotation);

				currentBullet++;
				if (currentBullet > 4) currentBullet = 0;

				currentBulletCooldown -= bulletCooldown;

			}
		}






	}
	else {
		rotation += 3.14f * timeStep;
	}

	for (int i = 0; i < 5; i++) {
		if (gunFire[i]->IsDamaging())
			gunFire[i]->Update(timeStep, collisionMap);

		if (Collision::isCollidingCircle(gunFire[i]->GetX(), gunFire[i]->GetY(), gunFire[i]->GetSize(), c.GetX(), c.GetY(), c.GetSize()) && gunFire[i]->IsDamaging()) {
			//player dead



		}
	}
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


}

void RangedEnemy::Init(float colour[3], Texture* texture) {

	bullet.Init("res/textures/sprites/bullet.png");

	for (int i = 0; i < 5; i++) {

		gunFire.emplace_back((new ThrowingRock(0.3f, 0.3f, 0.f, 0.f, 0.f, 0.15f, false, false, false, 1.f)));
		gunFire[i]->Init(colour, &bullet);
	}



	Sprite::Init(colour, texture);
}

RangedEnemy::~RangedEnemy()
{
}
