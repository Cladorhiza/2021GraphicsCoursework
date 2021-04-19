#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>

#include "Shader.h"
#include "Renderer.h"
#include "Entity.h"
#include "Rectangle.h"
#include "Sprite.h"
#include "not_my_code/glm/glm.hpp"
#include "not_my_code/glm/gtc/matrix_transform.hpp"
#include "TextureManager.h"
#include "InputManager.h"
#include "Util.h"
#include "Character.h"
#include "Collision.h"
#include "Enemy.h"
#include "PatrolEnemy.h"
#include "RangedEnemy.h"
#include "TileMap.h"


int main(void) {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;



	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1664, 936, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Error initialising glew" << std::endl;

	glfwSetWindowSizeLimits(window, 1664, 936, 1664, 936);

	std::cout << "Current OpenGL version: " << glGetString(GL_VERSION) << std::endl;


	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	Shader shader("../res/shaders/Basic.shader");
	Renderer renderer;
	glm::mat4 viewMatrix(1.0f);
	glm::mat4 projectionMatrix = glm::ortho(0.f, 72.f, 0.f, 40.5f);

	InputManager inputManager;
	TextureManager textureManager;
	TileMap tilemap(64, 32);
	tilemap.InitTiles(textureManager, "../res/maps/default/TextureMap.csv");

	std::vector<std::vector<int>> collisionMap = Collision::LoadCollisionMapFromFile("../res/maps/default/CollisionMap.csv");

	std::vector<std::string> texStrings;
	texStrings.emplace_back("barrel");
	texStrings.emplace_back("bush");
	texStrings.emplace_back("cave");
	texStrings.emplace_back("cavewood");
	texStrings.emplace_back("dirt");
	texStrings.emplace_back("door");
	texStrings.emplace_back("grass");
	texStrings.emplace_back("sand");
	texStrings.emplace_back("testground");
	texStrings.emplace_back("thatch");
	texStrings.emplace_back("tree");
	texStrings.emplace_back("water");
	texStrings.emplace_back("window");
	texStrings.emplace_back("woodwall");


	std::unordered_map<std::string, int> TextureNamesToCollision;
	for (std::string s : texStrings) {

		if (s == "dirt" || s == "sand" || s == "grass")
			TextureNamesToCollision[s] = 0;
		else TextureNamesToCollision[s] = 1;
	}



	int currentString = 0;
	bool aDown = false;
	bool dDown = false;
	bool sDown = false;
	float mouseX;
	float mouseY;
	float xRatio = 1664.f / 72.f;
	float yRatio = 936.f / 40.5f;

	float red[] = {1.f, 0.f, 0.f};
	Sprite currentPaintingTexture(5.f, 5.f, 68.f, 4.f, 0.f);
	currentPaintingTexture.Init(red, textureManager.GetTileTexture("barrel"));
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		//reset openGL
		glClearColor(0.0f, 0.0f, 0.0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		
		/* Render here */
		

		mouseY = (936.f - inputManager.getMouseY()) / yRatio;
		mouseX = inputManager.getMouseX() / xRatio;

		if (inputManager.getKeyState(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

			
			//std::cout << mouseX << ", " << mouseY << std::endl;

			if (mouseX < 64 && mouseY < 32)
			{
				TileMap::Tile& t = tilemap.GetTileByCoordinate(mouseX, mouseY);
				std::cout << t.x << ", " << t.y << std::endl;
	
				tilemap.SetTileTextureByCoordinateAlreadyBuilt(t.x, t.y, texStrings[currentString]);
				
				collisionMap[t.x][t.y] = TextureNamesToCollision[texStrings[currentString]];

				
			}
		}

		if (inputManager.getKeyState(GLFW_KEY_A) == GLFW_PRESS && !aDown) {
			currentString--;
			if (currentString < 0) currentString = texStrings.size() - 1;

			aDown = true;
		}
		else if (inputManager.getKeyState(GLFW_KEY_A) == GLFW_RELEASE)
			aDown = false;


		if (inputManager.getKeyState(GLFW_KEY_D) == GLFW_PRESS && !dDown) {
			currentString++;
			if (currentString >= texStrings.size()) currentString = 0;

			dDown = true;
		}
		else if (inputManager.getKeyState(GLFW_KEY_D) == GLFW_RELEASE)
			dDown = false;

		if (inputManager.getKeyState(GLFW_KEY_S) == GLFW_PRESS && !sDown) {

			std::ofstream tMap;
			tMap.open("../res/maps/editorMap/TextureMap.csv");
			tMap << tilemap.ExportAsString();
			tMap.close();

			std::ofstream cMap;
			cMap.open("../res/maps/editorMap/CollisionMap.csv");
			cMap << Collision::ToString(collisionMap);
			cMap.close();

			sDown = true;
		}
		else if (inputManager.getKeyState(GLFW_KEY_S) == GLFW_RELEASE)
			sDown = false;

		currentPaintingTexture.SetTexture(textureManager.GetTileTexture(texStrings[currentString]));
		
		
		renderer.DrawTileMap(tilemap, shader, projectionMatrix, viewMatrix);
		renderer.DrawQuad(currentPaintingTexture, shader);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		inputManager.Poll(window);
	}
	glfwTerminate();
	return 0;
}