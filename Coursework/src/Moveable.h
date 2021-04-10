#pragma once
#include "Sprite.h"
#include "InputManager.h"
#include "not_my_code/glm/glm.hpp"
class Moveable : public Sprite
{
protected:
	glm::vec2 velocity;
	float size;
public:
	Moveable(float width, float height, float positionX, float positionY, float positionZ, float size);
	virtual void Move(float timeStep) = 0;
	~Moveable();
	inline void SetVelocity(glm::vec2 v) { velocity = v; }
	inline glm::vec2& GetVelocity() { return velocity; }
	inline void SetSize(float s) { size = s; }
	inline float GetSize() { return size; }
	bool isCollidingCircle(Moveable& m);
	virtual bool isCollidingRectangle(int x, int y);
};

