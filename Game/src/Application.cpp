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
#include "LevelOne.h"
#include "LevelTwo.h"

#define GLEW_STATIC

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


	InputManager inputManager;
	Shader shader("../res/shaders/Basic.shader");
	
	LevelOne levelOne(inputManager);
	bool playingLevelOne = true;
	bool firstTimeLevelOne = true;
	
	LevelTwo levelTwo(inputManager);
	bool playingLevelTwo = false;
	bool firstTimeLevelTwo = true;
	

	//delta time code
	std::chrono::steady_clock::time_point timePrevious = std::chrono::steady_clock::now();
	float cumElapsed = 0.f;
	int frameCount = 0;


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		//delta time code
		std::chrono::steady_clock::time_point timeCurrent = std::chrono::steady_clock::now();
		float elapsed = ((float)std::chrono::duration_cast<std::chrono::microseconds>(timeCurrent - timePrevious).count()) / 1000000;
		timePrevious = std::chrono::steady_clock::now();

		//display framerate in console
		frameCount++;
		cumElapsed += elapsed;
		if (cumElapsed > 1) {
			cumElapsed = 0;
			frameCount = 0;
		}

		//reset openGL
		glClearColor(0.0f, 0.0f, 0.0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (playingLevelOne) {
			if (firstTimeLevelOne) {
				firstTimeLevelOne = false;
				levelOne.Init();
			}
			levelOne.Update(elapsed);
			levelOne.Render(shader);
		}
		if (playingLevelTwo) {
			if (firstTimeLevelTwo) {
				firstTimeLevelTwo = false;
				levelTwo.Init();
			}
			levelTwo.Update(elapsed);
			levelTwo.Render(shader);
		}






		if (levelOne.IsCompleted()) {
			playingLevelOne = false;
			playingLevelTwo = true;
			levelOne.End();
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		inputManager.Poll(window);
	}
	glfwTerminate();
	return 0;
}