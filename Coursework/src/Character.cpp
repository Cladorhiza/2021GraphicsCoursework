#include "Character.h"



Character::Character(float width, float height, float positionX, float positionY, float positionZ, float size, float movementSpeed)
	:Moveable(width, height, positionX, positionY, positionZ, size), movementSpeed(movementSpeed)
{
	
}

void Character::Move(float timeStep) {
	Translate(velocity.x * timeStep, velocity.y * timeStep, 0.0f);
}

void Character::Move(float timeStep, InputManager& inputManager) {
	velocity.x = 0;
	velocity.y = 0;
	bool isMoving = false;
	if (inputManager.getKeyState(GLFW_KEY_W) == GLFW_PRESS || inputManager.getKeyState(GLFW_KEY_W) == GLFW_REPEAT) {
		velocity.y = movementSpeed;
		isMoving = true;
	}
	
	if (inputManager.getKeyState(GLFW_KEY_A) == GLFW_PRESS || inputManager.getKeyState(GLFW_KEY_A) == GLFW_REPEAT) {
		velocity.x = -movementSpeed;
		isMoving = true;
	}

	if (inputManager.getKeyState(GLFW_KEY_S) == GLFW_PRESS || inputManager.getKeyState(GLFW_KEY_S) == GLFW_REPEAT) {
		velocity.y = -movementSpeed;
		isMoving = true;
	}

	if (inputManager.getKeyState(GLFW_KEY_D) == GLFW_PRESS || inputManager.getKeyState(GLFW_KEY_D) == GLFW_REPEAT) {
		velocity.x = movementSpeed;
		isMoving = true;
	}

	if (isMoving) {

		velocity = glm::normalize(velocity) * movementSpeed;
		Move(timeStep);
	}
	else velocity = glm::vec2(0.f, 0.f);
}

Character::~Character()
{
}
