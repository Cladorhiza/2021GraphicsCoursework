#pragma once
#include "Sprite.h"



class Tile : public Sprite
{
protected:
static const float TILE_SIDE_LENGTH;
public:
	Tile(float positionX, float positionY, float positionZ);
	~Tile();
};

