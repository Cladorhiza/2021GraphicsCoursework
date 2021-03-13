#include "TileMap.h"



TileMap::TileMap(int sizeX, int sizeY)
	:worldXMax(sizeX), worldYMax(sizeY)
{


	for (int i = 0; i < sizeX; i++) {

		for (int j = 0; j < sizeY; j++) {

			Tile t((float)i, (float)j, 0.0f);

			tiles.push_back(t);

		}

	}

}

void TileMap::InitTiles(TextureManager& textureManager) {
	
	std::vector<std::string> texNames = textureManager.LoadTileTextures("res/maps/testMap/TextureMap.csv");
	float defaultTileColours[3]{ 1.0f, 1.0f, 1.0f };

	if (texNames.size() != tiles.size()) {
		//LOGWARNING
	}

	for (int i = 0; i < tiles.size(); i++) {

		tiles[i].Init(defaultTileColours, textureManager.GetTexture(texNames[i]));
	}
}

TileMap::~TileMap()
{
}

std::vector<Tile>::iterator TileMap::begin() {
	return tiles.begin();
}
std::vector<Tile>::iterator TileMap::end() {
	return tiles.end();
}
