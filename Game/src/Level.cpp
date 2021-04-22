#include "Level.h"



Level::Level(const std::string& mapName, InputManager& inputManager)
	:mapName(mapName),
	inputManager(inputManager),
	player(1.f, 1.f, 0.f, 0.f, 0.f, 0.4f, 5.f),
	tileMap(64, 32),
	viewMatrix(1.f),
	projectionMatrix(glm::ortho(0.f, 16.f, 0.f, 9.f)),
	colours{1.f, 1.f, 1.f},
	completed(false)
{
	

}

void Level::Init() {

	//map
	tileMap.InitTiles(textureManager, MAP_DIRECTORY + mapName + "/TextureMap.csv");
	textureManager.LoadSpriteTextures(MAP_DIRECTORY + mapName + "/TextureNames.csv");
	collisionMap = Collision::LoadCollisionMapFromFile(MAP_DIRECTORY + mapName + "/CollisionMap.csv");

	//animations
	std::vector<std::vector<Texture*>> animations;
	std::vector<std::string> leftFrames{ "character_left1", "character_left2" };
	std::vector<std::string> rightFrames{ "character_right1", "character_right2" };
	std::vector<std::string> upFrames{ "character_up1", "character_up2" };
	std::vector<std::string> downFrames{ "character_down1", "character_down2" };

	std::vector<Texture*> leftAnimation = textureManager.GetSpriteTextures(leftFrames);
	std::vector<Texture*> rightAnimation = textureManager.GetSpriteTextures(rightFrames);
	std::vector<Texture*> upAnimation = textureManager.GetSpriteTextures(upFrames);
	std::vector<Texture*> downAnimation = textureManager.GetSpriteTextures(downFrames);

	animations.push_back(leftAnimation);
	animations.push_back(rightAnimation);
	animations.push_back(upAnimation);
	animations.push_back(downAnimation);

	//player
	player.Init(colours, textureManager.GetSpriteTexture("character_idle"), animations);



}

void Level::Render(Shader& shader) {


	//centre camera on player
	viewMatrix = glm::mat4(1.f);
	viewMatrix = glm::translate(viewMatrix, glm::vec3(-player.GetX() + 8.f, -player.GetY() + 4.5f, -player.GetZ()));

	renderer.DrawTileMap(tileMap, shader, projectionMatrix, viewMatrix);
	renderer.DrawCharacter(player, shader);

	for (RangedEnemy& r : rangedEnemies) {
		if (r.IsAlive())
			renderer.DrawRangedEnemy(r, shader);
	}
	for (PatrolEnemy& p : patrolEnemies) {
		if (p.IsAlive())
			renderer.DrawQuad(p, shader);
	}
}

Level::~Level()
{
}