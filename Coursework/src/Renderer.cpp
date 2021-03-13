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
}


void Renderer::DrawTileMap(TileMap& tilemap, Shader& shader, const glm::mat4& projectionMatrix) {

	shader.Bind();
	shader.SetUniformMat4f("ProjectionMatrix", projectionMatrix);
	for (Tile& t : tilemap) {

		t.Bind();
		shader.SetUniformvec3f("worldPosition", t.GetX(), t.GetY(), t.GetZ());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareIndexBuffer);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}