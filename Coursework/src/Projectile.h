#pragma once
#include "Moveable.h"
class Projectile : public Moveable
{
protected:
	bool damaging;
	bool bouncy;
public:
	Projectile(float width, float height, float positionX, float positionY, float positionZ, float size, bool damaging, bool bouncy);
	~Projectile();
	void Move(float timeStep);
	bool isCollidingRectangle(int rectX, int rectY) override;
	inline void SetDamaging(bool d) { damaging = d; }
	inline bool IsDamaging() { return damaging; }
};

