#pragma once
class Entity
{
protected:
	float x;
	float y;
	float z;
public:
	Entity();
	Entity(float positionX, float positionY, float positionZ);
	~Entity();
	inline float GetX() {return x;}
	inline float GetY() {return y;}
	inline float GetZ() {return z;}
	inline void Translate(float positionX, float positionY, float positionZ) { x += positionX; y += positionY; z += positionZ; }
	
};

