#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Util.h"
class Collision
{
public:
	Collision();

	static std::vector<std::vector<int>> LoadCollisionMapFromFile(const std::string& filePath);
	static std::vector<std::pair<int, int>> GetPotentialRectangleCollidersForCircle(std::vector<std::vector<int>>& collisionMap, float x, float y, float size);
	static bool isCollidingCircle(float x1, float y1, float r1, float x2, float y2, float r2);
	~Collision();
};

