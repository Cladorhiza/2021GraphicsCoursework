#pragma once
#include <vector>

#include "TextureManager.h"
class TileMap
{
protected:
	struct Tile;
	std::vector<Tile> tiles;
	std::vector<Texture> textures;
	int worldXMax;
	int worldYMax;
	std::unordered_map<std::string, int> uniqueTexturesNames;
	std::vector<float> vertexes;
	std::vector<unsigned> indexes;
	unsigned vbo, vao, ibo;
	TextureManager* manager;
public:
	TileMap(int sizeX, int sizeY);
	void InitTiles(TextureManager& textureManager);
	~TileMap();
	std::vector<Tile>::iterator begin();
	std::vector<Tile>::iterator end();
	void Bind();
	void Unbind();
	int Size();
};

