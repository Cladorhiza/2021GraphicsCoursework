#include <GL/glew.h>

#include "TileMap.h"



TileMap::TileMap(int sizeX, int sizeY)
	:worldXMax(sizeX), worldYMax(sizeY), manager(nullptr), vbo(0), vao(0), ibo(0)
{

	//pushback a tile for each unit of space in tilemap
	for (int i = 0; i < sizeY; i++) {

		for (int j = 0; j < sizeX; j++) {

			Tile t;
			t.x = static_cast<float>(j);
			t.y = static_cast<float>(i);
			t.z = 0.0f;
			t.texIndex = 0.f;

			tiles.push_back(t);

		}

	}

}

//builds opengl geometry by pushing back one tile at a time inside vertex vector
void TileMap::InitTiles(TextureManager& textureManager, const std::string& textureMapPath) {
	
	manager = &textureManager;
	std::vector<std::pair<std::string, int>> texNamesAndCounts = textureManager.LoadTileTextures(textureMapPath);
	int uniqueTexCount = 0;
	int indexCount = 0;
	size_t tileIndex = 0;
	int tileCount = 0;
	
	//for each pair of texName : counts
	for (std::pair<std::string, int>& p : texNamesAndCounts) {
		
		//track current tile number
		tileCount += p.second;

		//loop as many times as we have tiles of this type
		for (int i = 0; i < p.second; i++) {

			//if tile texture is not in our map of texNames to unique texture IDs
			if (uniqueTexturesNames.find(p.first) == uniqueTexturesNames.end()) {
				//add it and increase the count of unique textures
				uniqueTexturesNames[p.first] = uniqueTexCount;
				uniqueTexCount++;
			}
			//set the texture information for the tile
			tiles[tileIndex].texIndex = static_cast<float>(uniqueTexturesNames[p.first]);

			//push 4 quad coords
			
			
			vertexes.push_back(tiles[tileIndex].x);
			vertexes.push_back(tiles[tileIndex].y);
			vertexes.push_back(0.0f + tiles[tileIndex].z);
			vertexes.push_back(1.0f);
			vertexes.push_back(1.0f);
			vertexes.push_back(1.0f);
			vertexes.push_back(0.0f);
			vertexes.push_back(0.0f);
			vertexes.push_back(tiles[tileIndex].texIndex);

			vertexes.push_back(tiles[tileIndex].x);
			vertexes.push_back(1.0f + tiles[tileIndex].y);
			vertexes.push_back(0.0f + tiles[tileIndex].z);
			vertexes.push_back(1.0f);
			vertexes.push_back(1.0f);
			vertexes.push_back(1.0f);
			vertexes.push_back(0.0f);
			vertexes.push_back(1.0f);
			vertexes.push_back(tiles[tileIndex].texIndex);

			vertexes.push_back(1.0f + tiles[tileIndex].x);
			vertexes.push_back(1.0f + tiles[tileIndex].y);
			vertexes.push_back(0.0f + tiles[tileIndex].z);
			vertexes.push_back(1.0f);
			vertexes.push_back(1.0f);
			vertexes.push_back(1.0f);
			vertexes.push_back(1.0f);
			vertexes.push_back(1.0f);
			vertexes.push_back(tiles[tileIndex].texIndex);

			vertexes.push_back(1.0f + tiles[tileIndex].x);
			vertexes.push_back(tiles[tileIndex].y);
			vertexes.push_back(0.0f + tiles[tileIndex].z);
			vertexes.push_back(1.0f);
			vertexes.push_back(1.0f);
			vertexes.push_back(1.0f);
			vertexes.push_back(1.0f);
			vertexes.push_back(0.0f);
			vertexes.push_back(tiles[tileIndex].texIndex);

			indexes.push_back(0 + indexCount);
			indexes.push_back(1 + indexCount);
			indexes.push_back(2 + indexCount);
			indexes.push_back(3 + indexCount);
			indexes.push_back(2 + indexCount);
			indexes.push_back(0 + indexCount);


			indexCount += 4;
			tileIndex++;

			if (uniqueTexCount > 32) {
				//LOGWARNING
			}

		}

	}

	if (tileCount != tiles.size()) {
		printf("size mismatch error");
		//LOGWARNING
	}
	
	build();

}

TileMap::~TileMap()
{
}

std::vector <TileMap::Tile> ::iterator TileMap::begin() {
	return tiles.begin();
}
std::vector<TileMap::Tile>::iterator TileMap::end() {
	return tiles.end();
}

void TileMap::Bind() {
	glBindVertexArray(vao);
	for (std::pair<const std::string, int>& t : uniqueTexturesNames) {
		manager->GetTileTexture(t.first)->Bind(t.second);
	}
}
void TileMap::Unbind() {

	for (int i = 0; i < 32; i++){
		glBindTextureUnit(i, 0);
	}
	glActiveTexture(0);
	glBindVertexArray(0);
}

int TileMap::Size() {
	return static_cast<int>(tiles.size());
}

TileMap::Tile& TileMap::GetTileByCoordinate(float x, float y) {

	return tiles[((int)x + ((int)y * worldXMax))];
}

void TileMap::SetTileTextureByCoordinateAlreadyBuilt(float x, float y, const std::string texName) {
	int texID = uniqueTexturesNames[texName];

	//hacky hard code nonsense resetting texture ID's then rebuilding the openGL geometry
	vertexes[36*((int)x + ((int)y * worldXMax)) + 8]  = static_cast<float>(texID);
	vertexes[36*((int)x + ((int)y * worldXMax)) + 17] = static_cast<float>(texID);
	vertexes[36*((int)x + ((int)y * worldXMax)) + 26] = static_cast<float>(texID);
	vertexes[36*((int)x + ((int)y * worldXMax)) + 35] = static_cast<float>(texID);

	GetTileByCoordinate(x, y).texIndex = static_cast<float>(uniqueTexturesNames[texName]);

	build();
}
void TileMap::build() {

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexes.size(), vertexes.data(), GL_STATIC_DRAW);

	glEnableVertexArrayAttrib(vao, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)0);

	glEnableVertexArrayAttrib(vao, 1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)(3 * sizeof(float)));

	glEnableVertexArrayAttrib(vao, 2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)(6 * sizeof(float)));

	glEnableVertexArrayAttrib(vao, 3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)(8 * sizeof(float)));


	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * indexes.size(), indexes.data(), GL_STATIC_DRAW);




}

//used to export to file
std::string TileMap::ExportAsString() {


	std::unordered_map<int, std::string> indexToTexName;

	for (std::pair<std::string, int> p : uniqueTexturesNames) {
		indexToTexName[p.second] = p.first;
	}

	std::string fileString = "";

	int currentTexIndex = 0;
	int tilesInARow = 0;

	for (int i = 0; i < 32; i++) {

		for (int j = 0; j < 64; j++) {

			Tile& t = GetTileByCoordinate(j, i);

			if (j == 0 && i == 0) {
				currentTexIndex = t.texIndex;
				fileString += indexToTexName[currentTexIndex];
			}

			if (t.texIndex != currentTexIndex) {

				fileString += ", ";
				fileString += std::to_string(tilesInARow);
				fileString += "\n";

				
				currentTexIndex = t.texIndex;
				fileString += indexToTexName[currentTexIndex];
				tilesInARow = 1;
			}
			else {
				tilesInARow++;
			}

		}


	}

	fileString += ", ";
	fileString += std::to_string(tilesInARow);

	return fileString;


}