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
	struct Tile {
		float x, y, z;
		float texIndex;
	};
	TileMap(int sizeX, int sizeY);
	void InitTiles(TextureManager& textureManager, const std::string& textureMapPath);
	~TileMap();
	std::vector<Tile>::iterator begin();
	std::vector<Tile>::iterator end();
	void Bind();
	void Unbind();
	int Size();
	inline std::unordered_map<std::string, int>& GetUniqueTextureNames() { return uniqueTexturesNames; }
	Tile& GetTileByCoordinate(float x, float y);
	void build();
	void SetTileTextureByCoordinateAlreadyBuilt(float x, float y, const std::string texName);
	std::string ExportAsString();
};

