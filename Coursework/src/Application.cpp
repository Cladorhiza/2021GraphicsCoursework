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

int main(void) {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;



	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(960, 960, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	/* Loop until the user closes the window */
	if (glewInit() != GLEW_OK)
		std::cout << "Error initialising glew" << std::endl;

	std::cout << "Current OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	Shader shader("res/shaders/Basic.shader");
	Renderer renderer;

	TextureManager textureManager;
	
	glm::mat4 viewMatrix(1.0f);
	glm::mat4 projectionMatrix = glm::ortho(-0.5f, 5.5f, -0.5f, 3.5f);
	Sprite s(30.f, 30.f, 30.f, 30.f, 0.f);
	TileMap tilemap(6,4);
	tilemap.InitTiles(textureManager);

	
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f,0.2f,0.2f,1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		/* Render here */
		std::cout << "pog";
		
		renderer.DrawTileMap(tilemap, shader, projectionMatrix, viewMatrix);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}