#pragma once
#include <vector>
#include "Texture.h"
#include <unordered_map>
class TextureManager
{
private:
	std::unordered_map<std::string, Texture> textureMap;
	const std::string TILES_PATH = "res/textures/tiles/";
	const std::string FILE_EXTENSION = ".png";
public:	

	TextureManager();
	std::vector<std::pair<std::string, int>> LoadTileTextures(const std::string& FilePath);
	~TextureManager();
	Texture& GetTexture(const std::string& name);
};

