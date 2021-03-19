#include "TextureManager.h"

#include <sstream>
#include <fstream>

#include "Util.h"


TextureManager::TextureManager()
{
}

std::vector<std::pair<std::string,int>> TextureManager::LoadTileTextures(const std::string& FilePath)
{
	std::vector<std::pair<std::string, int>> texNamesAndCount;
	std::vector<std::string> texNameAndCount;
	std::string fileLine;
	std::fstream file(FilePath);
	std::stringstream ss;
	if (!file.good()) {
		//LOGWARNING
		printf("Incorrect path to textures");
		return texNamesAndCount;
	}

	while (std::getline(file, fileLine)) {

		texNameAndCount = Util::split(fileLine, ",");

		std::pair<std::string, int> p(texNameAndCount[0], std::stoi(texNameAndCount[1]));

		
		textureMap.emplace(p.first, TILES_PATH + p.first + FILE_EXTENSION);
		texNamesAndCount.push_back(p);
	}
	
	return texNamesAndCount;
}
Texture& TextureManager::GetTexture(const std::string& name) {
	if (textureMap.find(name) == textureMap.end()) {
		//LOGWARNING
		printf("default tex for name: %s\n", name);
		return textureMap[name];
	}
	return textureMap[name];
}
TextureManager::~TextureManager()
{
}