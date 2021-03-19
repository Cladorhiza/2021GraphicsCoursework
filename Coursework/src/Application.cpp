#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Shader.h"
#include "Renderer.h"
#include "Entity.h"
#include "Rectangle.h"
#include "Sprite.h"
#include "not_my_code/glm/glm.hpp"
#include "not_my_code/glm/gtc/matrix_transform.hpp"
#include "TextureManager.h"

bool W;
bool A;
bool S;
bool D;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		W = true;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		A = true;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		S = true;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		D = true;
	}
	if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		W = false;
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		A = false;
	}
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		S = false;
	}
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		D = false;
	}




}

int main(void) {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;



	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640,640, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	if (glewInit() != GLEW_OK)
		std::cout << "Error initialising glew" << std::endl;

	glfwSetKeyCallback(window, key_callback);

	std::cout << "Current OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader shader("res/shaders/Basic.shader");
	Renderer renderer;
	glm::mat4 viewMatrix(1.0f);
	glm::mat4 projectionMatrix = glm::ortho(0.f,8.f,0.f,8.f);
	


	TextureManager textureManager;
	TileMap tilemap(24,16);
	tilemap.InitTiles(textureManager);
	textureManager.LoadSpriteTextures("res/maps/testMap/TextureNames.csv");


	Sprite s(1.f, 1.f, 0.f, 0.f, 0.f);
	float colours[] = { 0.f, 0.f, 0.f };
	s.Init(colours, textureManager.GetSpriteTexture("animu_schoolgirl"));


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f,0.0f,0.0f,1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		if (W) s.Translate(0.f, 0.001f, 0.f);
		if (A) s.Translate(-0.001f, 0.0f, 0.f);
		if (S) s.Translate(0.f, -0.001f, 0.f);
		if (D) s.Translate(0.001f, 0.0f, 0.f);
		

		viewMatrix = glm::mat4(1.f);
		viewMatrix = glm::translate(viewMatrix, glm::vec3(-s.GetX()+4.f, -s.GetY()+4.f, -s.GetZ()));

		
		
		/* Render here */
		renderer.DrawTileMap(tilemap, shader, projectionMatrix, viewMatrix);
		glEnable(GL_BLEND);
		renderer.DrawQuad(s, shader);
		glDisable(GL_BLEND);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}