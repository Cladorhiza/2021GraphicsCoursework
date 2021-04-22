#include "LevelTwo.h"




LevelTwo::LevelTwo(InputManager& inputManager)
	:Level("LevelTwo", inputManager),
	soundEngine(irrklang::createIrrKlangDevice()),
	victoryText(3.f, 3.f, 48.f, 19.f, 0.f),
	victory(false),
	firstTimeVictory(true)
{



}
void LevelTwo::Init() {

	static bool firstInit = true;
	if (firstInit) {
		Level::Init();
		firstInit = false;
		soundEngine->play2D("../res/audio/dungeon.mp3", true);
		soundEngine->setSoundVolume(0.15f);
		victoryTextTex.Init("../res/textures/sprites/victory.png");
		victoryText.Init(colours, &victoryTextTex);
	}

	player.SetPosition(11.f, 13.f, 0.f);
	player.SetAlive(true);
	player.GetRock().SetDamaging(false);



	//clear enemies when respawning
	patrolEnemies.clear();
	rangedEnemies.clear();

	//patrol enemies
	PatrolEnemy patrolMan(1.f, 1.f, 20.f, 15.f, 0.f, 0.5f, 3.f, 2.f);
	patrolMan.setPatrols(glm::vec2(20.f, 15.f), glm::vec2(25.f, 15.f));
	AddPatrolEnemy(patrolMan);
	PatrolEnemy patrolMan1(1.f, 1.f, 34.f, 16.f, 0.f, 0.5f, 3.f, 2.f);
	patrolMan1.setPatrols(glm::vec2(34.f, 16.f), glm::vec2(34.f, 14.f));
	AddPatrolEnemy(patrolMan1);
	PatrolEnemy patrolMan2(1.f, 1.f, 37.5f, 17.5f, 0.f, 0.5f, 3.f, 2.f);
	patrolMan2.setPatrols(glm::vec2(37.5f, 17.5f), glm::vec2(37.f, 12.5f));
	AddPatrolEnemy(patrolMan2);
	PatrolEnemy patrolMan3(1.f, 1.f, 50.f, 18.5f, 0.f, 0.5f, 3.f, 2.f);
	patrolMan3.setPatrols(glm::vec2(50.f, 18.5f), glm::vec2(50.5f, 15.5f));
	AddPatrolEnemy(patrolMan3);
	

	for (auto& patrol : patrolEnemies) {
		patrol.Init(colours, textureManager.GetSpriteTexture("canj"));
	}

	//ranged enemies
	AddRangedEnemy(1.f, 1.f, 17.f, 16.f, 0.f, 0.5, 3.5f, 0.f);
	AddRangedEnemy(1.f, 1.f, 17.f, 14.f, 0.f, 0.5, 3.5f, 0.f);
	AddRangedEnemy(1.f, 1.f, 28.5f, 17.5f, 0.f, 0.5, 3.5f, 0.f);
	AddRangedEnemy(1.f, 1.f, 43.5f, 16.5f, 0.f, 0.5, 3.5f, 0.f);
	AddRangedEnemy(1.f, 1.f, 47.5f, 18.5f, 0.f, 0.5, 3.5f, 0.f);
	AddRangedEnemy(1.f, 1.f, 48.f, 17.f, 0.f, 0.5, 3.5f, 0.f);
	AddRangedEnemy(1.f, 1.f, 52.5f, 18.f, 0.f, 0.5, 3.5f, 0.f);
	AddRangedEnemy(1.f, 1.f, 52.5f, 16.f, 0.f, 0.5, 3.5f, 0.f);

	for (auto& ranged : rangedEnemies) {
		ranged.Init(colours, textureManager.GetSpriteTexture("canj"));
	}





}


void LevelTwo::Update(float timeStep) {

	victory = true;
	//check if enemies alive, if so: update
	for (RangedEnemy& r : rangedEnemies) {
		if (r.IsAlive()) {
			r.Update(timeStep, player, collisionMap, soundEngine);
			victory = false;
		}
	}
	for (PatrolEnemy& p : patrolEnemies) {
		if (p.IsAlive()) {
			p.Update(timeStep, player, collisionMap, soundEngine);
			victory = false;
		}
	}

	player.Update(timeStep, inputManager, collisionMap, soundEngine);
	if (!player.IsAlive()) {
		Init();
	}
	
	if (victory && firstTimeVictory) {
		soundEngine->play2D("../res/audio/clapping.mp3");
		firstTimeVictory = false;
	}

}

void LevelTwo::Render(Shader& shader) {
	Level::Render(shader);

	if (victory) {
		renderer.DrawQuad(victoryText, shader);

	}

}

LevelTwo::~LevelTwo()
{
}
