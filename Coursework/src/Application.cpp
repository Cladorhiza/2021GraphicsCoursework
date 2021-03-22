#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

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

std::vector<std::vector<int>> LoadCollisionMapFromFile(const std::string& filePath) {

	std::vector<std::vector<int>> collisionMap;
	std::string fileLine;
	std::fstream file(filePath);
	std::stringstream ss;

	while (std::getline(file, fileLine)) {

		for (int i = 0; i < fileLine.size(); i++) {
			if (i >= collisionMap.size()) {

				std::vector<int> v;
				collisionMap.push_back(v);
			}

			collisionMap[i].insert(collisionMap[i].begin(), Util::CharDigitToInt(fileLine[i]));

		}
	}

	return collisionMap;
}

std::vector<std::pair<int, int>> GetPotentialRectangleCollidersForCircle(std::vector<std::vector<int>>& collisionMap, float x, float y, float size) {

	std::vector<std::pair<int, int>> potentialColliders;
	std::pair<int, int> circlepos((int)x,(int)y);

	int roundedSize = (int)round(size);

	std::pair<int, int> firstGridCheck(std::max(0, circlepos.first - roundedSize),std::max(0, circlepos.second - roundedSize));
	std::pair<int, int> lastGridCheck(std::min((int)collisionMap[0].size(), circlepos.first + roundedSize + 1), std::min((int)collisionMap.size(), circlepos.second + roundedSize + 1));

	for (int i = firstGridCheck.first; i < lastGridCheck.first; i++) {
		for (int j = firstGridCheck.second; j < lastGridCheck.second; j++) {
			if (collisionMap[i][j] == 1) {
				std::pair<int, int> p(i, j);
				potentialColliders.push_back(p);
			}
		}
	}
	return potentialColliders;
}

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


	Character s(1.f, 1.f, 3.f, 3.f, 0.f, .25f, 0.005f);
	float colours[] = { 0.f, 0.f, 0.f };
	s.Init(colours, textureManager.GetSpriteTexture("moon_caster"));

	std::vector<std::vector<int>> collisionMap = LoadCollisionMapFromFile("res/maps/testMap/CollisionMap.csv");

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





	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f,0.0f,0.0f,1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		viewMatrix = glm::mat4(1.f);
		viewMatrix = glm::translate(viewMatrix, glm::vec3(-s.GetX()+8.f, -s.GetY()+4.5f, -s.GetZ()));

		std::vector<std::pair<int, int>> candidateRECTS;
		s.Move(1.f, inputManager);
		std::vector<std::pair<int, int>> colls = GetPotentialRectangleCollidersForCircle(collisionMap, s.GetX(), s.GetY(), s.GetSize());

		for (std::pair<int,int> p : colls) {
			
			if (s.isCollidingRectangle(p.first, p.second)) {

				s.Move(-1.f);
				std::cout << "COCK";
				break;
			}
		}
		
		
		/* Render here */
		renderer.DrawTileMap(tilemap, shader, projectionMatrix, viewMatrix);
		glEnable(GL_BLEND);
		renderer.DrawQuad(s1, shader);
		renderer.DrawQuad(s2, shader);
		renderer.DrawQuad(s3, shader);
		renderer.DrawQuad(s4, shader);
		renderer.DrawQuad(s5, shader);
		renderer.DrawQuad(s6, shader);
		renderer.DrawQuad(s7, shader);
		renderer.DrawQuad(s8, shader);
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