#include "TextureManager.h"

#include <sstream>
#include <fstream>

#include "Util.h"


TextureManager::TextureManager()
{
}

std::vector<std::pair<std::string, int>> TextureManager::LoadTileTextures(const std::string& filePath)
{
	std::vector<std::pair<std::string, int>> texNamesAndCount;
	std::vector<std::string> texNameAndCount;
	std::string fileLine;
	std::fstream file(filePath);
	std::stringstream ss;
	if (!file.good()) {
		//LOGWARNING
		printf("Incorrect path to textures");
		return texNamesAndCount;
	}

	while (std::getline(file, fileLine)) {

		texNameAndCount = Util::split(fileLine, ",");

		//split counts of tex and texname
		std::pair<std::string, int> p(texNameAndCount[0], std::stoi(texNameAndCount[1]));

		//if that pair is not in map
		if (tileTextureMap.find(p.first) == tileTextureMap.end()) {
			//add it to map with filepath
			tileTextureMap.emplace(p.first, TILES_PATH + p.first + FILE_EXTENSION);
			printf("TileTexName: %s, ID: %i\n", fileLine.c_str(), tileTextureMap[p.first].GetID());
		}
		//build data to be returned
		texNamesAndCount.push_back(p);
	}
	
	return texNamesAndCount;
}

void TextureManager::LoadSpriteTextures(const std::string& filePath) {
	std::string fileLine;
	std::fstream file(filePath);
	std::stringstream ss;

	while (std::getline(file, fileLine)) {
		//load each texture into spriteTextureMap
		spriteTextureMap.emplace(fileLine, SPRITES_PATH + fileLine + FILE_EXTENSION);
		printf("SpriteTexName: %s, ID: %i\n", fileLine.c_str(), spriteTextureMap[fileLine].GetID());
	}
}

Texture* TextureManager::GetSpriteTexture(const std::string& name) {
	if (spriteTextureMap.find(name) == spriteTextureMap.end()) {
		//LOGWARNING
		printf("default tex for name: %s\n", name.c_str());
	}
	return &spriteTextureMap[name];
}

Texture* TextureManager::GetTileTexture(const std::string& name) {
	if (tileTextureMap.find(name) == tileTextureMap.end()) {
		//LOGWARNING
		printf("default tex for name: %s\n", name.c_str());
	}
	return &tileTextureMap[name];
}

std::vector<Texture*> TextureManager::GetSpriteTextures(const std::vector<std::string>& names) {

	std::vector<Texture*> textures;
	for (const std::string& s : names) {
		textures.push_back(GetSpriteTexture(s));
	}

	return textures;
}
TextureManager::~TextureManager()
{
}