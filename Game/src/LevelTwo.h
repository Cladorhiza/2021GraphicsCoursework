#pragma once
#include "Level.h"
class LevelTwo :
	public Level
{
protected:
	irrklang::ISoundEngine* soundEngine;
	float victoryCountdown;
	Sprite victoryText;
	Texture victoryTextTex;
	bool victory;
	bool firstTimeVictory;
public:
	LevelTwo(InputManager& inputManager);
	~LevelTwo();
	void Init();
	void Render(Shader& shader);
	void Update(float timeStep);
};

