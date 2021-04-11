#pragma once
#include "VertexArray.h"
#include "Shape.h"
#include "Shader.h"
#include "TileMap.h"
#include "Character.h"
#include "RangedEnemy.h"
class Renderer
{
private:
	unsigned squareIndexBuffer;
	
public:
	Renderer();
	~Renderer();
	void DrawQuad(Shape& sprite, Shader& shader);
	void DrawCharacter(Character& character, Shader& shader);
	void DrawRangedEnemy(RangedEnemy& enemy, Shader& shader);
	void DrawTileMap(TileMap& tilemap, Shader& shader, const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
};

