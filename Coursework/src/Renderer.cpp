#include "Renderer.h"



Renderer::Renderer()
{
	unsigned squareIndexes[6]{ 0,1,2,0,2,3 };
	glGenBuffers(1, &squareIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned), squareIndexes, GL_STATIC_DRAW);
}


Renderer::~Renderer()
{
}

void Renderer::DrawQuad(Shape& sprite, Shader& shader) {
	shader.Bind();
	sprite.Bind();
	shader.SetUniformvec3f("worldPosition", sprite.GetX(), sprite.GetY(), sprite.GetZ());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareIndexBuffer);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	shader.SetUniformvec3f("worldPosition", 0.0f,0.0f,0.0f);
}


void Renderer::DrawTileMap(TileMap& tilemap, Shader& shader, const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {

	static int textureUnits[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31 };
	shader.Bind();
	shader.SetUniformMat4f("ProjectionMatrix", projectionMatrix);
	shader.SetUniformMat4f("ViewMatrix", viewMatrix);
	shader.SetUniform1iv("diffuseMap", 32, textureUnits);
	tilemap.Bind();

	glDrawElements(GL_TRIANGLES, 6 * tilemap.Size() , GL_UNSIGNED_INT, nullptr);
	
}