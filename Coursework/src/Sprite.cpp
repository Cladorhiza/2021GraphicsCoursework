#include "Sprite.h"



Sprite::Sprite(float width, float height, float positionX, float positionY, float positionZ)
	: Rectangle(width, height, positionX, positionY, positionZ), texture(nullptr)
{
}


Sprite::~Sprite()
{
}

void Sprite::Init(float colour[3], Texture* texture) {
	Rectangle::Init(colour);

	unsigned TextureCoordinateBuffer;
	
	this->texture = texture;

	//texcoords
	float tex[8];
	tex[0] = 0.0f;	 tex[1] = 0.0f;
	tex[2] = 0.0f;	 tex[3] = 1.0f;
	tex[4] = 1.0f;	 tex[5] = 1.0f;
	tex[6] = 1.0f;	 tex[7] = 0.0f;

	glGenBuffers(1, &TextureCoordinateBuffer);
	//bind texture coords, add to vertex array
	glBindBuffer(GL_ARRAY_BUFFER, TextureCoordinateBuffer);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), tex, GL_STATIC_DRAW);
	va.AddBuffer(TextureCoordinateBuffer, 2);

	//disable binds
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

}

void Sprite::Bind() {
	Rectangle::Bind();
	texture->Bind();
}
void Sprite::Unbind() {
	Rectangle::Unbind();
	texture->Unbind();
}
