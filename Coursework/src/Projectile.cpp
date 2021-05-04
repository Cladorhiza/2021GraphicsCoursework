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

	//clamp the x and y of the projectile to the x and y range of the tile to get closest point of the circle to the tile
	glm::vec2 nearestPoint;
	nearestPoint.x = std::max((float)rectX, std::min(x, float(rectX + 1)));
	nearestPoint.y = std::max((float)rectY, std::min(y, float(rectY + 1)));
	
	//create a vector from the center of projectile to the clamped values
	glm::vec2 vecToNearest = nearestPoint - glm::vec2(x, y);
	//calculate the overlap by taking the magnitude of this vector away from the radius of the circle 
	float overlap = size - glm::length(vecToNearest);

	//prevent divide by 0 error
	if (std::isnan(overlap)) overlap = 0;

	//if collision
	if (overlap >= 0.f) {
		
		
		vecToNearest = glm::normalize(vecToNearest);

		//translate the object backwards away from the tile by the amount of overlap
		Translate(-vecToNearest.x * overlap, -vecToNearest.y * overlap, 0.0f);

		if (bouncy) {
			//check how close the x and y coordinates are to being integers
			float pointDiffx = std::abs(round(nearestPoint.x) - nearestPoint.x);
			float pointDiffy = std::abs(round(nearestPoint.y) - nearestPoint.y);

			//if hit side of tile
			if (pointDiffx < pointDiffy) {
				SetVelocity(glm::vec2(-velocity.x, velocity.y) * 0.8f);
			}
			//if hit corner of tile
			else if (pointDiffx == pointDiffy) {
				float speed = glm::length(velocity);
				SetVelocity(-vecToNearest * speed * 0.8f);
			}
			//if hit bottom/top of tile
			else {
				SetVelocity(glm::vec2(velocity.x, -velocity.y) * 0.8f);
			}

		}
		//if not bouncy, destroy on impact
		else 
			damaging = false;
		return true;
		 
	}
	return false;
}

Projectile::~Projectile()
{
}
