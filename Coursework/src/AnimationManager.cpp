#include "AnimationManager.h"


AnimationManager::AnimationManager(int ticksPerSec)
	:tickInterval(1.f / ticksPerSec), tick(0), dt(0.f)
{
	

}


AnimationManager::~AnimationManager()
{
}

void AnimationManager::Tick(float dt) {

	this->dt += dt;

	if (this->dt > tickInterval) {

		this->dt -= tickInterval;
		tick++;
		for (Animation& a : animations) {

			if (tick % a.ticksPerFrame == 0) {
				if (a.index < a.textures.size() - 1) {
					a.index++;
				}
				else a.index = 0;
				a.sprite->SetTexture(a.textures[a.index]);
			}
		}
	}

}