#include "Moveable.h"
#include <algorithm>



Moveable::Moveable(float width, float height, float positionX, float positionY, float positionZ, float size)
	:Sprite(width, height, positionX, positionY, positionZ), size(size)
{
	velocity = glm::vec2(0, 0);
}

bool Moveable::isCollidingCircle(Moveable& m) {
	
	return ((m.GetX() - x) * (m.GetX() - x) + (m.GetY() - y) * (m.GetY() - y)) < (m.GetSize() + size) * (m.GetSize() + size);
}
bool Moveable::isCollidingRectangle(int rectX, int rectY) {

	glm::vec2 nearestPoint;

	nearestPoint.x = std::max((float)rectX, std::min(x, float(rectX + 1)));
	nearestPoint.y = std::max((float)rectY, std::min(y, float(rectY + 1)));

	glm::vec2 vecToNearest = nearestPoint - glm::vec2(x, y);
	float overlap = size - glm::length(vecToNearest);
	
	return overlap > 0.f;
}

Moveable::~Moveable()
{
}
