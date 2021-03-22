#pragma once
#include "Moveable.h"
class Character : public Moveable
{
private:
	float movementSpeed;


public:
	Character(float width, float height, float positionX, float positionY, float positionZ, float size, float movementSpeed);
	~Character();
	virtual void Move(float timeStep);
	virtual void Move(float timeStep, InputManager& inputManager);
};

