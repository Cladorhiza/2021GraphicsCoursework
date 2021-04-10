#pragma once
#include "Moveable.h"
class Enemy :
	public Moveable
{
public:
	Enemy(float width, float height, float positionX, float positionY, float positionZ, float size);
	~Enemy();
};

