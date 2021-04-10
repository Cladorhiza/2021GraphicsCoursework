#include "InputManager.h"



InputManager::InputManager()
{
	keys[GLFW_KEY_W] = GLFW_RELEASE;
	keys[GLFW_KEY_A] = GLFW_RELEASE;
	keys[GLFW_KEY_S] = GLFW_RELEASE;
	keys[GLFW_KEY_D] = GLFW_RELEASE;
	keys[GLFW_KEY_L] = GLFW_RELEASE;
	keys[GLFW_KEY_K] = GLFW_RELEASE;
}

void InputManager::Poll(GLFWwindow* window) {

	glfwPollEvents();

	int state = glfwGetKey(window, GLFW_KEY_W);
	keys[GLFW_KEY_W] = state;
	state = glfwGetKey(window, GLFW_KEY_A);
	keys[GLFW_KEY_A] = state;
	state = glfwGetKey(window, GLFW_KEY_S);
	keys[GLFW_KEY_S] = state;
	state = glfwGetKey(window, GLFW_KEY_D);
	keys[GLFW_KEY_D] = state;	
	state = glfwGetKey(window, GLFW_KEY_L);
	keys[GLFW_KEY_L] = state;
	state = glfwGetKey(window, GLFW_KEY_K);
	keys[GLFW_KEY_K] = state;
	

}

int InputManager::getKeyState(int GLFWKeyCode) {
	return keys[GLFWKeyCode];
}

InputManager::~InputManager()
{
}
