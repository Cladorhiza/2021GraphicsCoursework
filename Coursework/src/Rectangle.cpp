#include "Rectangle.h"



Rectangle::Rectangle(float width, float height, float positionX, float positionY, float positionZ)
	: Shape(positionX, positionY, positionZ), width(width), height(height)
{
}


Rectangle::~Rectangle()
{

}

void Rectangle::Init(float colour[3]) {
	va.Bind();

	unsigned vertexBuffer, colourBuffer;
	float vert[12];

	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;

	//x,y,z values for each vertex
	vert[0] = -halfWidth; vert[1] = -halfHeight; vert[2] = 0.0;
	vert[3] = -halfWidth; vert[4] = halfHeight; vert[5] = 0.0;
	vert[6] = halfWidth; vert[7] = halfHeight; vert[8] = 0.0;
	vert[9] = halfWidth; vert[10] = -halfHeight; vert[11] = 0.0;

	glGenBuffers(1, &vertexBuffer);
	//bind vertices, add to vertex array
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vert, GL_STATIC_DRAW);
	va.AddBuffer(vertexBuffer, 3);

	// colour array
	float col[12];

	//r,g,b values for each vertex
	col[0] = colour[0]; col[1] = colour[1]; col[2] = colour[2];
	col[3] = colour[0]; col[4] = colour[1]; col[5] = colour[2];
	col[6] = colour[0]; col[7] = colour[1]; col[8] = colour[2];
	col[9] = colour[0]; col[10] = colour[1]; col[11] = colour[2];


	glGenBuffers(1, &colourBuffer);
	//bind colours, add to vertex array
	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), col, GL_STATIC_DRAW);
	va.AddBuffer(colourBuffer, 3);

	//disable binds
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Rectangle::Bind() {
	va.Bind();
}

void Rectangle::Unbind() {
	va.Unbind();
}