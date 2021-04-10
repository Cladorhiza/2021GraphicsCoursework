#include "Collision.h"



Collision::Collision()
{
}

std::vector<std::vector<int>> Collision::LoadCollisionMapFromFile(const std::string& filePath) {

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

std::vector<std::pair<int, int>> Collision::GetPotentialRectangleCollidersForCircle(std::vector<std::vector<int>>& collisionMap, float x, float y, float size) {

	std::vector<std::pair<int, int>> potentialColliders;
	std::pair<int, int> circlepos((int)x, (int)y);

	int roundedSize = (int)(size+1);

	std::pair<int, int> firstGridCheck(std::max(0, circlepos.first - roundedSize), std::max(0, circlepos.second - roundedSize));
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

Collision::~Collision()
{
}
