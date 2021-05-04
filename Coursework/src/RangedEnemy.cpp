#include "RangedEnemy.h"
#include "not_my_code/glm/gtx/rotate_vector.hpp"
#include <iostream>


RangedEnemy::RangedEnemy(float width, float height, float positionX, float positionY, float positionZ, float size, float scanRadius, float speed)
	:Enemy(width, height, positionX, positionY, positionZ, size, speed), scanRadius(scanRadius), currentBullet(0), bulletCooldown(0.5f), currentBulletCooldown(0.f)
{

}

void RangedEnemy::Move(float timeStep) {

	Translate(velocity.x * timeStep, velocity.y * timeStep, 0.0f);
}

void RangedEnemy::Update(float timeStep, Character& c, std::vector<std::vector<int>>& collisionMap, irrklang::ISoundEngine* soundEngine) {

	//check if character within scanrange
	bool attacking = Collision::IsCollidingCircle(x, y, scanRadius, c.GetX(), c.GetY(), c.GetSize());

	if (attacking) {
		
		//create a vector to the character to calculate dot product
		glm::vec2 vecToCharacter(c.GetX() - x, c.GetY() - y);
		glm::vec2 directionFacing(0.f,1.f);
		
		float dotProduct = glm::dot(directionFacing, vecToCharacter);

		//calculate angle to rotate to the player
		float angleToRotate = glm::acos(dotProduct / (glm::length(directionFacing) * glm::length(vecToCharacter)));

		//calculate which direction to rotate
		if (directionFacing.x * vecToCharacter.y + directionFacing.y * vecToCharacter.x > 0.f) {
			rotation = angleToRotate;
		}
		else
			rotation = -angleToRotate;

		//fires bullet every bullet cooldown up to a maximum of 5 in the world at a time
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
			gunFire[i]->Update(timeStep, collisionMap, soundEngine);

		if (Collision::IsCollidingCircle(gunFire[i]->GetX(), gunFire[i]->GetY(), gunFire[i]->GetSize(), c.GetX(), c.GetY(), c.GetSize()) && gunFire[i]->IsDamaging()) {
			//player dead
			c.SetAlive(false);
			soundEngine->play2D("../res/audio/rock hit.mp3");
		}
	}
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


}

void RangedEnemy::Init(float colour[3], Texture* texture) {

	bullet.Init("../res/textures/sprites/bullet.png");

	for (int i = 0; i < 5; i++) {

		gunFire.emplace_back((new ThrowingRock(0.3f, 0.3f, 0.f, 0.f, 0.f, 0.15f, false, false, false, 1.f)));
		gunFire[i]->Init(colour, &bullet);
	}



	Sprite::Init(colour, texture);
}

RangedEnemy::~RangedEnemy()
{
}

RangedEnemy::RangedEnemy(RangedEnemy&& other) 
	: RangedEnemy(other.width, other.height, other.x, other.y, other.z, other.size, other.scanRadius, other.speed)
{

	scanRadius = other.scanRadius;
	bullet.Init("../res/textures/sprites/bullet.png");
	currentBullet = other.currentBullet;
	bulletCooldown = other.bulletCooldown;
	currentBulletCooldown = other.currentBulletCooldown;



	for (auto& g : other.gunFire) {
		gunFire.push_back(std::move(g));
	}
}