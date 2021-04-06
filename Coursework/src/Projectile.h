#pragma once
#include "Moveable.h"
class Projectile : public Moveable
{
protected:
	bool damaging;
public:
	Projectile(float width, float height, float positionX, float positionY, float positionZ, float size, bool damaging);
	~Projectile();
	void Move(float timeStep);
	inline void SetDamaging(bool d) { damaging = d; }
	inline bool IsDamaging() { return damaging; }
};

