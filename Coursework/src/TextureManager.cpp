#include "TextureManager.h"

#include <sstream>
#include <fstream>


TextureManager::TextureManager()
{
}

std::vector<std::string> TextureManager::LoadTileTextures(const std::string& FilePath)
{
	std::vector<std::string> texNames;
	std::string texName;
	std::fstream file(FilePath);
	std::stringstream ss;
	if (!file.good()) {
		//LOGWARNING
		printf("Incorrect path to textures");
		return texNames;
	}

	while (std::getline(file, texName)) {
		if (textureMap.find(texName) == textureMap.end()) {
			textureMap.emplace(texName, TILES_PATH + texName + FILE_EXTENSION);
		}
		texNames.push_back(texName);
	}
	return texNames;
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