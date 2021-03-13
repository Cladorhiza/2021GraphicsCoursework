#pragma once
#include "Shape.h"
class Rectangle : public Shape
{
protected:
	float width;
	float height;
	VertexArray va;
public:
	Rectangle(float width, float height, float positionX, float positionY, float positionZ);
	~Rectangle();
	void Init(float colour[3]);
	void Bind() override;
	void Unbind() override;
};

