#include "Character.h"

#include <iostream>

#include "Collision.h"




Character::Character(float width, float height, float positionX, float positionY, float positionZ, float size, float movementSpeed)
	:Moveable(width, height, positionX, positionY, positionZ, size), 
	movementSpeed(movementSpeed), 
	animationTimer(0.f), 
	directionChanged(false), 
	swordSwing(nullptr), 
	isAlive(true), 
	swordSwinging(false)
{
	
}

void Character::Move(float timeStep) {
	Translate(velocity.x * timeStep, velocity.y * timeStep, 0.0f);
}

void Character::Update(float timeStep, InputManager& inputManager, std::vector<std::vector<int>>& collisionMap, irrklang::ISoundEngine* soundEngine) {
	
	
	//Sword Attack
	if (inputManager.getKeyState(GLFW_KEY_L) == GLFW_PRESS) {
		
		if (!swordSwinging) {
			soundEngine->play2D("../res/audio/sword swing.mp3");
			swordSwinging = true;
		}
		swordSwing->SetDamaging(true);
	}
	else {
		swordSwing->SetDamaging(false);
		swordSwinging = false;
	}

	if (swordSwing->IsDamaging()) {
		if (facingDown) {
			swordSwing->SetPosition(x, y - swordSwing->GetSize(), z);
			swordSwing->SetRotation(3.1415f);
		}
		else if (facingUp) {
			swordSwing->SetPosition(x, y + swordSwing->GetSize(), z);
			swordSwing->SetRotation(0.f);
		}
		else if (facingLeft) {
			swordSwing->SetPosition(x - swordSwing->GetSize(), y, z);
			swordSwing->SetRotation(4.7123f);
		}
		else if (facingRight) {
			swordSwing->SetPosition(x + swordSwing->GetSize(), y, z);
			swordSwing->SetRotation(1.5708f);
		}
		//if not moving
		else {
			swordSwing->SetPosition(x, y - swordSwing->GetSize(), z);
			swordSwing->SetRotation(3.1415f);
		}
	}
	//Throwing Attack
	if (rockThrow->IsDamaging()) {

		rockThrow->Update(timeStep, collisionMap, soundEngine);
	}
	else if (inputManager.getKeyState(GLFW_KEY_K) == GLFW_PRESS && glm::length(velocity) > 0.05f) {

		rockThrow->Reset(x, y, z, velocity);
	}

	//WASD movement
	glm::vec2 currentVelocity(velocity);
	velocity.x = 0;
	velocity.y = 0;
	isMoving = false;
	
	//if sword not damaging, enable movement
	if (!swordSwing->IsDamaging()) {

		if (inputManager.getKeyState(GLFW_KEY_W) == GLFW_PRESS || inputManager.getKeyState(GLFW_KEY_W) == GLFW_REPEAT) {
			velocity.y = movementSpeed;
			isMoving = true;
			facingUp = true;
		}
		else facingUp = false;

		if (inputManager.getKeyState(GLFW_KEY_A) == GLFW_PRESS || inputManager.getKeyState(GLFW_KEY_A) == GLFW_REPEAT) {
			velocity.x = -movementSpeed;
			isMoving = true;
			facingLeft = true;
		}
		else facingLeft = false;

		if (inputManager.getKeyState(GLFW_KEY_S) == GLFW_PRESS || inputManager.getKeyState(GLFW_KEY_S) == GLFW_REPEAT) {
			velocity.y = -movementSpeed;
			isMoving = true;
			facingDown = true;
		}
		else facingDown = false;

		if (inputManager.getKeyState(GLFW_KEY_D) == GLFW_PRESS || inputManager.getKeyState(GLFW_KEY_D) == GLFW_REPEAT) {
			velocity.x = movementSpeed;
			isMoving = true;
			facingRight = true;
		}
		else facingRight = false;

	}
	
	//if movement input and not using sword, move
	if (isMoving && !swordSwing->IsDamaging()) {
		if (velocity != currentVelocity) directionChanged = true;
		velocity = glm::normalize(velocity) * movementSpeed;
		Move(timeStep);
	}
	else velocity = glm::vec2(0.f, 0.f);

	Animate(timeStep, soundEngine);

	//basic collisions between player and terrain
	std::vector<std::pair<int, int>> colls = Collision::GetPotentialRectangleCollidersForCircle(collisionMap, x, y, size);

	for (std::pair<int, int> p : colls) {

		isCollidingRectangle(p.first, p.second);

	}
}

void Character::Animate(float timeStep, irrklang::ISoundEngine* soundEngine) {

	//if changing direction, reset animation frames
	if (directionChanged) { 
		animationCounter = 0;
		directionChanged = false;
	}
	
	
	if (!swordSwing->IsDamaging()) 
		animationTimer += timeStep;

	//swap frames every 0.1 seconds
	if (animationTimer > 0.1f) {
		if (facingUp) {
			SetTexture(upAnimation[animationCounter % upAnimation.size()]);
		}
		else if (facingLeft) {
			SetTexture(leftAnimation[animationCounter % leftAnimation.size()]);
		}
		else if (facingDown) {
			SetTexture(downAnimation[animationCounter % downAnimation.size()]);
		}
		else if (facingRight) {
			SetTexture(rightAnimation[animationCounter % rightAnimation.size()]);
		}
		else SetTexture(idle);
		animationTimer -= 0.1f;
		animationCounter++;
	}
}


void Character::Init(float colour[3], Texture* texture, std::vector<std::vector<Texture*>> animations) {

	
	sword.Init("../res/textures/sprites/sword_swing.png");
	swordSwing.reset(new Projectile(1.f, 1.f, 0.f, 0.f, 0.f, 0.5f, false, false));
	swordSwing->Init(colour, &sword);

	rock.Init("../res/textures/sprites/throwing_rock.png");
	rockThrow.reset(new ThrowingRock(0.3f, 0.3f, 0.f, 0.f, 0.f, 0.15f, false, true, true, 5.f));
	rockThrow->Init(colour, &rock);

	idle = texture;
	leftAnimation = animations[0];
	rightAnimation = animations[1];
	upAnimation = animations[2];
	downAnimation = animations[3];
	Sprite::Init(colour, texture);
}

Character::~Character()
{
}
