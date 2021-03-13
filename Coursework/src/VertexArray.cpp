#include "VertexArray.h"



VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id);
}


VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &id);
}

void VertexArray::Bind() const {
	glBindVertexArray(id);
}
void VertexArray::Unbind() const {
	glBindVertexArray(0);
}
void VertexArray::AddBuffer(unsigned buffer, unsigned int countPerVert) {

	Bind();
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	glVertexAttribPointer(vertAttribCount, countPerVert, GL_FLOAT, GL_FALSE,  countPerVert * sizeof(float), 0);
	glEnableVertexAttribArray(vertAttribCount);
	vertAttribCount++;
}