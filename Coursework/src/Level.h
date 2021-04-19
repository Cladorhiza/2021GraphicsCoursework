#pragma once
#include <vector>
#include "PatrolEnemy.h"
#include "RangedEnemy.h"
#include "Character.h"
#include "TextureManager.h"


class Level
{
private:
	Character* player;
	std::vector<PatrolEnemy> patrolEnemies;
	std::vector<RangedEnemy> rangedEnemies;
	TextureManager textureManager;
public:
	Level();
	~Level();
};

