#pragma once
#include "Entity.h"
#include "VertexArray.h"
#include <string>
#include "Texture.h"
class Shape : public Entity
{
protected:
public:
	Shape(float positionX, float positionY, float positionZ);
	~Shape();
	virtual void Bind() = 0;
	virtual void Unbind() = 0;
};