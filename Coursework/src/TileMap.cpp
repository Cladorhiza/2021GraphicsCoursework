#include <GL/glew.h>

#include "TileMap.h"

struct TileMap::Tile{
	float x, y, z;
	float texIndex;
};

TileMap::TileMap(int sizeX, int sizeY)
	:worldXMax(sizeX), worldYMax(sizeY), manager(nullptr)
{


	for (int i = 0; i < sizeY; i++) {

		for (int j = 0; j < sizeX; j++) {

			Tile t;
			t.x = j;
			t.y = i;
			t.z = 0.0f;
			t.texIndex = 0.f;

			tiles.push_back(t);

		}

	}

}

void TileMap::InitTiles(TextureManager& textureManager) {
	
	manager = &textureManager;
	std::vector<std::pair<std::string, int>> texNamesAndCounts = textureManager.LoadTileTextures("res/maps/testMap/TextureMap.csv");
	int uniqueTexCount = 0;
	int indexCount = 0;
	size_t tileIndex = 0;

	//if (texNames.size() != tiles.size()) {
	//	printf("size mismatch error");
	//	//LOGWARNING
	//}

	for (std::pair<std::string, int>& p : texNamesAndCounts) {

		for (int i = 0; i < p.second; i++) {

			if (uniqueTexturesNames.find(p.first) == uniqueTexturesNames.end()) {
				uniqueTexturesNames[p.first] = uniqueTexCount;
				uniqueTexCount++;
			}
			tiles[tileIndex].texIndex = uniqueTexturesNames[p.first];

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
		manager->GetTileTexture(t.first).Bind(t.second);
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
	return tiles.size();
}