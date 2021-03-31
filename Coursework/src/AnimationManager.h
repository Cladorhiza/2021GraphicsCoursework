#pragma once
#include <vector>

#include "Texture.h"
#include "Sprite.h"

struct Animation {

	std::vector<Texture*> textures;
	Sprite* sprite;
	int ticksPerFrame;
	int index;
};

class AnimationManager
{
private:
	float tickInterval;
	int tick;
	float dt;
	std::vector<Animation> animations;

public:
	AnimationManager(int ticksPerSec);
	void Tick(float dt);
	~AnimationManager();
	inline void AddAnimation(const Animation& a) { animations.push_back(a); }
};

