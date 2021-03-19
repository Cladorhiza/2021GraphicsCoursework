#pragma once
#include <vector>
#include "Texture.h"
#include <unordered_map>
class TextureManager
{
private:
	std::unordered_map<std::string, Texture> tileTextureMap;
	std::unordered_map<std::string, Texture> spriteTextureMap;
	const std::string TILES_PATH = "res/textures/tiles/";
	const std::string SPRITES_PATH = "res/textures/sprites/";
	const std::string FILE_EXTENSION = ".png";
public:	

	TextureManager();
	std::vector<std::pair<std::string, int>> LoadTileTextures(const std::string& filePath);
	void LoadSpriteTextures(const std::string& filePath);
	Texture& GetSpriteTexture(const std::string& name);
	Texture& GetTileTexture(const std::string& name);
	~TextureManager();
};

