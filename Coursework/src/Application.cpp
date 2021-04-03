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


	Shader shader("res/shaders/Basic.shader");
	Renderer renderer;
	glm::mat4 viewMatrix(1.0f);
	glm::mat4 projectionMatrix = glm::ortho(0.f,16.f,0.f,9.f);
	
	InputManager inputManager;
	TextureManager textureManager;
	TileMap tilemap(10,10);
	tilemap.InitTiles(textureManager);
	textureManager.LoadSpriteTextures("res/maps/testMap/TextureNames.csv");


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
	

	Character s(1.f, 1.f, 3.f, 3.f, 0.f, .25f, 5.f);
	float colours[] = { 0.f, 0.f, 0.f };
	s.Init(colours, textureManager.GetSpriteTexture("character_idle"), animations);

	std::vector<std::vector<int>> collisionMap = Collision::LoadCollisionMapFromFile("res/maps/testMap/CollisionMap.csv");
	std::vector<Sprite> sprites;

	Sprite s1(1.f, 1.f, 0.5f, 5.5f, 0.f);
	Sprite s2(1.f, 1.f, 1.5f, 5.5f, 0.f);
	Sprite s3(1.f, 1.f, 2.5f, 5.5f, 0.f);
	Sprite s4(1.f, 1.f, 3.5f, 5.5f, 0.f);
	Sprite s5(1.f, 1.f, 6.5f, 5.5f, 0.f);
	Sprite s6(1.f, 1.f, 7.5f, 5.5f, 0.f);
	Sprite s7(1.f, 1.f, 8.5f, 5.5f, 0.f);
	Sprite s8(1.f, 1.f, 9.5f, 5.5f, 0.f);
	s1.Init(colours, textureManager.GetSpriteTexture("gravestone"));
	s2.Init(colours, textureManager.GetSpriteTexture("gravestone"));
	s3.Init(colours, textureManager.GetSpriteTexture("gravestone"));
	s4.Init(colours, textureManager.GetSpriteTexture("gravestone"));
	s5.Init(colours, textureManager.GetSpriteTexture("gravestone"));
	s6.Init(colours, textureManager.GetSpriteTexture("gravestone"));
	s7.Init(colours, textureManager.GetSpriteTexture("gravestone"));
	s8.Init(colours, textureManager.GetSpriteTexture("gravestone"));


	sprites.push_back(s1);
	sprites.push_back(s2);
	sprites.push_back(s3);
	sprites.push_back(s4);
	sprites.push_back(s5);
	sprites.push_back(s6);
	sprites.push_back(s7);
	sprites.push_back(s8);
	
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
			std::cout << frameCount << "fps" << std::endl;
			frameCount = 0;
		}
		glClearColor(0.0f,0.0f,0.0f,1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		viewMatrix = glm::mat4(1.f);
		viewMatrix = glm::translate(viewMatrix, glm::vec3(-s.GetX()+8.f, -s.GetY()+4.5f, -s.GetZ()));

		std::vector<std::pair<int, int>> candidateRECTS;
		s.Move(elapsed, inputManager);
		std::vector<std::pair<int, int>> colls = Collision::GetPotentialRectangleCollidersForCircle(collisionMap, s.GetX(), s.GetY(), s.GetSize());

		for (std::pair<int,int> p : colls) {
			
			if (s.isCollidingRectangle(p.first, p.second)) {

				s.Move(-elapsed);
				break;
			}
		}
		
		
		/* Render here */
		renderer.DrawTileMap(tilemap, shader, projectionMatrix, viewMatrix);
		glEnable(GL_BLEND);

		for (Sprite& sproit : sprites) {
			renderer.DrawQuad(sproit, shader);
		}
		
		renderer.DrawQuad(s, shader);

		glDisable(GL_BLEND);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		inputManager.Poll(window);
	}
	glfwTerminate();
	return 0;
}