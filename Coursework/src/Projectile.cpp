#include "Projectile.h"
#include <algorithm>


Projectile::Projectile(float width, float height, float positionX, float positionY, float positionZ, float size, bool damaging, bool bouncy)
	:Moveable(width, height, positionX, positionY, positionZ, size), damaging(damaging), bouncy(bouncy)
{
}

void Projectile::Move(float timeStep) {
	Translate(velocity.x * timeStep, velocity.y * timeStep, 0.0f);
}

bool Projectile::isCollidingRectangle(int rectX, int rectY) {

	glm::vec2 nearestPoint;
	nearestPoint.x = std::max((float)rectX, std::min(x, float(rectX + 1)));
	nearestPoint.y = std::max((float)rectY, std::min(y, float(rectY + 1)));
	
	glm::vec2 vecToNearest = nearestPoint - glm::vec2(x, y);
	float overlap = size - glm::length(vecToNearest);

	if (std::isnan(overlap)) overlap = 0;

	if (overlap >= 0.f) {
		
		vecToNearest = glm::normalize(vecToNearest);

		Translate(-vecToNearest.x * overlap, -vecToNearest.y * overlap, 0.0f);
		if (bouncy) {
			float pointDiffx = std::abs(round(nearestPoint.x) - nearestPoint.x);
			float pointDiffy = std::abs(round(nearestPoint.y) - nearestPoint.y);
			if (pointDiffx < pointDiffy) {
				SetVelocity(glm::vec2(-velocity.x, velocity.y) * 0.8f);
			}
			else if (pointDiffx == pointDiffy) {
				float speed = glm::length(velocity);
				SetVelocity(-vecToNearest * speed * 0.8f);
			}
			else {
				SetVelocity(glm::vec2(velocity.x, -velocity.y) * 0.8f);
			}

		}
		else 
			damaging = false;
		return true;
		 
	}
	return false;
}

Projectile::~Projectile()
{
}
