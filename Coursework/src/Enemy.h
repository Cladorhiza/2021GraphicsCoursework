#pragma once
#include "Moveable.h"
#include "Character.h"
class Enemy :
	public Moveable
{
protected:
	float speed;
	bool alive;
public:
	Enemy(float width, float height, float positionX, float positionY, float positionZ, float size, float speed);
	~Enemy();
	inline bool IsAlive() { return alive; }
};

