#include "LevelOne.h"



LevelOne::LevelOne(InputManager& inputManager)
	:Level("LevelOne", inputManager),
	controlScreen(8.f, 4.5f, 10.f, 8.f, 0.f),
	soundEngine(irrklang::createIrrKlangDevice()),
	displayHelp(false),
	helpSprite(4.f, 4.f, 23.5f, 19.5f, 0.f)
{



}
void LevelOne::Init() {

	static bool firstInit = true;
	if (firstInit) {
		Level::Init();
		firstInit = false;
		controls.Init("../res/textures/sprites/controls.png");
		controlScreen.Init(colours, &controls);
		help.Init("../res/textures/sprites/help.png");
		helpSprite.Init(colours, &help);
		soundEngine->play2D("../res/audio/harmony.mp3", true);
		soundEngine->setSoundVolume(0.15f);

	}

	player.SetPosition(14.f, 8.f, 0.f);
	player.SetAlive(true);
	player.GetRock().SetDamaging(false);



	//clear enemies when respawning
	patrolEnemies.clear();
	rangedEnemies.clear();

	//patrol enemies
	PatrolEnemy patrolMan(1.f, 1.f, 10.5f, 15.5f, 0.f, 0.5f, 3.f, 2.f);
	patrolMan.setPatrols(glm::vec2(10.5f, 15.5f), glm::vec2(13.5f, 14.5f));
	AddPatrolEnemy(patrolMan);
	PatrolEnemy patrolMan1(1.f, 1.f, 19.f, 19.f, 0.f, 0.5f, 3.f, 2.f);
	patrolMan1.setPatrols(glm::vec2(19.f, 19.f), glm::vec2(19.f, 17.f));
	AddPatrolEnemy(patrolMan1);
	PatrolEnemy patrolMan2(1.f, 1.f, 27.5f, 12.5f, 0.f, 0.5f, 3.f, 2.f);
	patrolMan2.setPatrols(glm::vec2(27.5f, 12.5f), glm::vec2(29.5f, 12.5f));
	AddPatrolEnemy(patrolMan2);
	PatrolEnemy patrolMan3(1.f, 1.f, 31.5f, 9.5f, 0.f, 0.5f, 3.f, 2.f);
	patrolMan3.setPatrols(glm::vec2(31.5f, 9.5f), glm::vec2(34.5f, 9.5f));
	AddPatrolEnemy(patrolMan3);
	PatrolEnemy patrolMan4(1.f, 1.f, 38.5f, 14.5f, 0.f, 0.5f, 3.f, 2.f);
	patrolMan4.setPatrols(glm::vec2(38.5f, 14.5f), glm::vec2(41.5f, 14.5f));
	AddPatrolEnemy(patrolMan4);
	PatrolEnemy patrolMan5(1.f, 1.f, 30.5f, 16.5f, 0.f, 0.5f, 3.f, 2.f);
	patrolMan5.setPatrols(glm::vec2(30.5f, 16.5f), glm::vec2(33.5f, 16.5f));
	AddPatrolEnemy(patrolMan5);
	PatrolEnemy patrolMan6(1.f, 1.f, 37.5f, 19.5f, 0.f, 0.5f, 3.f, 2.f);
	patrolMan6.setPatrols(glm::vec2(37.5f, 19.5f), glm::vec2(40.5f, 17.5f));
	AddPatrolEnemy(patrolMan6);
	PatrolEnemy patrolMan7(1.f, 1.f, 43.5f, 10.5f, 0.f, 0.5f, 3.f, 2.f);
	patrolMan7.setPatrols(glm::vec2(43.5f, 10.5f), glm::vec2(43.5f, 8.5f));
	AddPatrolEnemy(patrolMan7);
	PatrolEnemy patrolMan8(1.f, 1.f, 48.5f, 22.5f, 0.f, 0.5f, 3.f, 2.f);
	patrolMan8.setPatrols(glm::vec2(48.5f, 22.5f), glm::vec2(51.5f, 22.5f));
	AddPatrolEnemy(patrolMan8);
	PatrolEnemy patrolMan9(1.f, 1.f, 52.5f, 21.5f, 0.f, 0.5f, 3.f, 2.f);
	patrolMan9.setPatrols(glm::vec2(52.5f, 21.5f), glm::vec2(54.5f, 21.5f));
	AddPatrolEnemy(patrolMan9);

	for (auto& patrol : patrolEnemies) {
		patrol.Init(colours, textureManager.GetSpriteTexture("canj"));
	}

	//ranged enemies
	AddRangedEnemy(1.f, 1.f, 11.5f, 16.5f, 0.f, 0.5, 3.5f, 0.f);
	AddRangedEnemy(1.f, 1.f, 14.5f, 15.5f, 0.f, 0.5, 3.5f, 0.f);
	AddRangedEnemy(1.f, 1.f, 30.f, 7.5f, 0.f, 0.5, 3.5f, 0.f);
	AddRangedEnemy(1.f, 1.f, 42.5f, 8.5f, 0.f, 0.5, 3.5f, 0.f);
	AddRangedEnemy(1.f, 1.f, 46.5f, 11.5f, 0.f, 0.5, 3.5f, 0.f);
	AddRangedEnemy(1.f, 1.f, 31.5f, 14.5f, 0.f, 0.5, 3.5f, 0.f);
	AddRangedEnemy(1.f, 1.f, 49.5f, 24.5f, 0.f, 0.5, 3.5f, 0.f);
	AddRangedEnemy(1.f, 1.f, 53.5f, 24.5f, 0.f, 0.5, 3.5f, 0.f);

	for (auto& ranged : rangedEnemies) {
		ranged.Init(colours, textureManager.GetSpriteTexture("canj"));
	}





}


void LevelOne::Update(float timeStep) {

	//check if enemies alive, if so: update
	for (RangedEnemy& r : rangedEnemies) {
		if (r.IsAlive()) {
			r.Update(timeStep, player, collisionMap, soundEngine);
		}
	}
	for (PatrolEnemy& p : patrolEnemies) {
		if (p.IsAlive()) {
			p.Update(timeStep, player, collisionMap, soundEngine);
		}
	}

	player.Update(timeStep, inputManager, collisionMap, soundEngine);
	if (!player.IsAlive()) {
		Init();
	}

	if (Collision::IsCollidingCircle(player.GetX(), player.GetY(), player.GetSize(), 23.5f, 19.5f, 4.f))
		displayHelp = true;
	else displayHelp = false;
	if (Collision::IsCollidingCircle(player.GetX(), player.GetY(), player.GetSize(), 51.5f, 26.5f, 0.25f))
		completed = true;
}

void LevelOne::Render(Shader& shader) {

	Level::Render(shader);

	renderer.DrawQuad(controlScreen, shader);
	
	if (displayHelp)
		renderer.DrawQuad(helpSprite, shader);


}

void LevelOne::End() {
	soundEngine->removeAllSoundSources();
}
LevelOne::~LevelOne()
{
}
