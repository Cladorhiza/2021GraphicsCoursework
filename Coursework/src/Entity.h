#pragma once
#include "not_my_code/glm/glm.hpp"
class Entity
{
protected:
	float x;
	float y;
	float z;
	float rotation;
public:
	Entity();
	Entity(float positionX, float positionY, float positionZ);
	~Entity();
	inline float GetX() {return x;}
	inline float GetY() {return y;}
	inline float GetZ() {return z;}
	inline void Translate(float positionX, float positionY, float positionZ) { x += positionX; y += positionY; z += positionZ; }
	inline void SetPosition(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	inline void SetRotation(float angle) { 
		rotation = angle;
	}
	inline float GetRotation() { return rotation; }
};

