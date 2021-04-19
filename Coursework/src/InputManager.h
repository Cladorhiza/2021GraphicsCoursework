#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>


class InputManager
{
private:
	std::unordered_map<int, int> keys;
	double xpos, ypos;
public:
	InputManager();
	void Poll(GLFWwindow* window);
	int getKeyState(int GLFWKeyCode);
	~InputManager();
	inline double getMouseX() { return xpos; }
	inline double getMouseY() { return ypos; }
};

