#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>


class InputManager
{
private:
	std::unordered_map<int, int> keys;
public:
	InputManager();
	void Poll(GLFWwindow* window);
	int getKeyState(int GLFWKeyCode);
	~InputManager();
};

