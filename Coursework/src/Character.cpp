#include "Character.h"
#include <iostream>



Character::Character(float width, float height, float positionX, float positionY, float positionZ, float size, float movementSpeed)
	:Moveable(width, height, positionX, positionY, positionZ, size), movementSpeed(movementSpeed), animationTimer(0.f), directionChanged(false), swordSwing(nullptr)
{
	
}

void Character::Move(float timeStep) {
	Translate(velocity.x * timeStep, velocity.y * timeStep, 0.0f);
}

void Character::Update(float timeStep, InputManager& inputManager) {

	//Attacks
	if (inputManager.getKeyState(GLFW_KEY_L) == GLFW_PRESS) {
		swordSwing->SetDamaging(true);
	}
	else swordSwing->SetDamaging(false);

	if (swordSwing->IsDamaging()) {
		if (facingDown) {
			swordSwing->SetPosition(GetX(), GetY() - swordSwing->GetSize(), GetZ());
			swordSwing->SetRotation(3.1415f);
		}
		else if (facingUp) {
			swordSwing->SetPosition(GetX(), GetY() + swordSwing->GetSize(), GetZ());
			swordSwing->SetRotation(0.f);
		}
		else if (facingLeft) {
			swordSwing->SetPosition(GetX() - swordSwing->GetSize(), GetY(), GetZ());
			swordSwing->SetRotation(4.7123f);
		}
		else if (facingRight) {
			swordSwing->SetPosition(GetX() + swordSwing->GetSize(), GetY(), GetZ());
			swordSwing->SetRotation(1.5708f);
		}
		//if not moving
		else {
			swordSwing->SetPosition(GetX(), GetY() - swordSwing->GetSize(), GetZ());
			swordSwing->SetRotation(3.1415f);
		}
	}

	//WASD movement
	glm::vec2 currentVelocity(velocity);
	velocity.x = 0;
	velocity.y = 0;
	isMoving = false;
	
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
	
	if (isMoving && !swordSwing->IsDamaging()) {
		if (velocity != currentVelocity) directionChanged = true;
		velocity = glm::normalize(velocity) * movementSpeed;
		Move(timeStep);
	}
	else velocity = glm::vec2(0.f, 0.f);
	Animate(timeStep);
}

void Character::Animate(float timeStep) {

	if (directionChanged) { 
		animationCounter = 0;
		directionChanged = false;
	}
	
	
	if (swordSwing->IsDamaging()) 
			swordSwing->SetRotation(swordSwing->GetRotation() + timeStep * 500);
	else animationTimer += timeStep;

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


	sword.Init("res/textures/sprites/sword_swing.png");
	swordSwing.reset(new Projectile(1.f, 1.f, 0.f, 0.f, 0.f, 1.f, false));
	swordSwing->Init(colour, &sword);



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
