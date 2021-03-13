#include "Tile.h"

const float Tile::TILE_SIDE_LENGTH = 1.0f;

Tile::Tile(float positionX, float positionY, float positionZ)
	:Sprite(TILE_SIDE_LENGTH, TILE_SIDE_LENGTH,  positionX,  positionY,  positionZ)
{

}


Tile::~Tile()
{
}
