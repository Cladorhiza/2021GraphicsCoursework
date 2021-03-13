#pragma once
#include <GL/glew.h>
#include <vector>
class VertexArray
{
private:
	unsigned id;
	unsigned vertAttribCount = 0;
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void AddBuffer(unsigned buffer, unsigned int count);
};

