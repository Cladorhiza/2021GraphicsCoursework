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


int main(void) {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;



	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1024, 576, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	if (glewInit() != GLEW_OK)
		std::cout << "Error initialising glew" << std::endl;

	glfwSetWindowSizeLimits(window, 1024, 576, 1024, 576);

	std::cout << "Current OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	Shader shader("../res/shaders/Basic.shader");
	Renderer renderer;
	InputManager inputManager;
	glm::mat4 viewMatrix(1.0f);
	glm::mat4 projectionMatrix = glm::ortho(0.f,16.f,0.f,9.f);
	
	TextureManager textureManager;
	TileMap tilemap(64,32);
	tilemap.InitTiles(textureManager, "../res/maps/editorMap/TextureMap.csv");
	textureManager.LoadSpriteTextures("../res/maps/editorMap/TextureNames.csv");


	std::vector<std::vector<Texture*>> animations;
	std::vector<std::string> leftFrames{"character_left1", "character_left2"};
	std::vector<std::string> rightFrames{"character_right1", "character_right2"};
	std::vector<std::string> upFrames{"character_up1", "character_up2"};
	std::vector<std::string> downFrames{"character_down1", "character_down2"};

	std::vector<Texture*> leftAnimation = textureManager.GetSpriteTextures(leftFrames);
	std::vector<Texture*> rightAnimation = textureManager.GetSpriteTextures(rightFrames);
	std::vector<Texture*> upAnimation = textureManager.GetSpriteTextures(upFrames);
	std::vector<Texture*> downAnimation = textureManager.GetSpriteTextures(downFrames);

	animations.push_back(leftAnimation);
	animations.push_back(rightAnimation);
	animations.push_back(upAnimation);
	animations.push_back(downAnimation);
	






	std::vector<std::vector<int>> collisionMap = Collision::LoadCollisionMapFromFile("../res/maps/editorMap/CollisionMap.csv");
	std::vector<Sprite> sprites;

	Character s(1.f, 1.f, 15.f, 10.f, 0.f, .5f, 5.f);
	float colours[] = { 0.f, 0.f, 0.f };
	s.Init(colours, textureManager.GetSpriteTexture("character_idle"), animations);

	PatrolEnemy foadster(1.f, 1.f, 8.f, 8.f, 0.f, 0.5f, 3.f, 2.f);
	foadster.setPatrols(glm::vec2(8.f, 8.f), glm::vec2(2.f, 8.f));
	foadster.Init(colours, textureManager.GetSpriteTexture("canj"));
	
	RangedEnemy rangedGimp(1.f, 1.f, 14.f, 18.f, 0.f, 0.5, 3.5f, 0.f);
	rangedGimp.Init(colours, textureManager.GetSpriteTexture("canj"));

	//delta time code
	std::chrono::steady_clock::time_point timePrevious = std::chrono::steady_clock::now();
	float cumElapsed = 0.f;
	int frameCount = 0;


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		//delta time code
		std::chrono::steady_clock::time_point timeCurrent = std::chrono::steady_clock::now();
		float elapsed = ((float)std::chrono::duration_cast<std::chrono::microseconds>(timeCurrent - timePrevious).count())/1000000;
		timePrevious = std::chrono::steady_clock::now();

		//display framerate in console
		frameCount++;
		cumElapsed += elapsed;
		if (cumElapsed > 1) {
			cumElapsed = 0;
			std::cout << s.GetX() << ", " << s.GetY() << std::endl;
			frameCount = 0;
		}
		
		//reset openGL
		glClearColor(0.0f,0.0f,0.0f,1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		//set up camera centered on player
		viewMatrix = glm::mat4(1.f);
		viewMatrix = glm::translate(viewMatrix, glm::vec3(-s.GetX()+8.f, -s.GetY()+4.5f, -s.GetZ()));

		if (foadster.IsAlive())
			foadster.Update(elapsed, s, collisionMap);
		if (rangedGimp.IsAlive()) 
			rangedGimp.Update(elapsed, s, collisionMap);
		

		
		s.Update(elapsed, inputManager, collisionMap);
		
		/* Render here */
		renderer.DrawTileMap(tilemap, shader, projectionMatrix, viewMatrix);
		glEnable(GL_BLEND);

		for (Sprite& sproit : sprites) {
			renderer.DrawQuad(sproit, shader);
		}
		renderer.DrawCharacter(s, shader);
		if (foadster.IsAlive()) 
			renderer.DrawQuad(foadster, shader);
		if (rangedGimp.IsAlive())
			renderer.DrawRangedEnemy(rangedGimp, shader);


		glDisable(GL_BLEND);
		
		
		
		
		
		
		
		
		
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		inputManager.Poll(window);
	}
	glfwTerminate();
	return 0;
}