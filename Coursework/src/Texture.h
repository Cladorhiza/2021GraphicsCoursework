#pragma once
#include <string>
#include "not_my_code/stb_image/stb_image.h"
class Texture
{
private:
	unsigned id;

public:
	Texture();
	Texture(const std::string filePath);
	void Init(const std::string filePath);
	~Texture();
	void Bind();
	void Bind(int slot);
	void Unbind();
	inline unsigned GetID() { return id; }
};

