#pragma once
#include "Rectangle.h"
class Sprite : public Rectangle
{
protected:
	Texture* texture;
	
public:
	Sprite(float width, float height, float positionX, float positionY, float positionZ);
	~Sprite();
	void Init(float colour[3], Texture& texture);
	void Bind() override;
	void Unbind() override;
};