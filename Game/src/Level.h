#pragma once
#include <vector>
#include "PatrolEnemy.h"
#include "RangedEnemy.h"
#include "Character.h"
#include "TextureManager.h"
#include "TileMap.h"
#include "Collision.h"
#include "Renderer.h"
#include "InputManager.h"
#include "irrKlang.h"

class Level
{
protected:
	const std::string MAP_DIRECTORY = "../res/maps/";
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	InputManager& inputManager;
	std::string mapName;
	TextureManager textureManager;
	TileMap tileMap;
	std::vector<std::vector<int>> collisionMap;
	Renderer renderer;
	Character player;
	std::vector<PatrolEnemy> patrolEnemies;
	std::vector<RangedEnemy> rangedEnemies;
	bool completed;
	float colours[3];
public:
	Level(const std::string& mapDir, InputManager& inputManager);
	~Level();
	virtual void Init();
	virtual void Update(float timeStep) = 0;
	virtual void Render(Shader& shader);
	inline void AddPatrolEnemy(PatrolEnemy& p) { 
		patrolEnemies.push_back(p); }
	inline void AddRangedEnemy(float width, float height, float positionX, float positionY, float positionZ, float size, float scanRadius, float speed){
		rangedEnemies.emplace_back(width, height, positionX, positionY, positionZ, size, scanRadius, speed);
	}
	inline bool IsCompleted() { return completed; }
};