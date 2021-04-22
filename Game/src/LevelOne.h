#pragma once
#include "Level.h"
class LevelOne : public Level
{
protected:
	Sprite controlScreen;
	Texture controls;
	Sprite helpSprite;
	Texture help;
	bool displayHelp;
	irrklang::ISoundEngine* soundEngine;
public:
	LevelOne(InputManager& inputManager);
	~LevelOne();
	void Init();
	void Render(Shader& shader);
	void Update(float timeStep);
	void End();
};

