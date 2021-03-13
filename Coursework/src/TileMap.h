#pragma once
#include <vector>

#include "Tile.h"
#include "TextureManager.h"
class TileMap
{
protected:
	std::vector<Tile> tiles;
	std::vector<Texture> textures;
	int worldXMax;
	int worldYMax;
public:
	TileMap(int sizeX, int sizeY);
	void InitTiles(TextureManager& textureManager);
	~TileMap();
	std::vector<Tile>::iterator begin();
	std::vector<Tile>::iterator end();
};

