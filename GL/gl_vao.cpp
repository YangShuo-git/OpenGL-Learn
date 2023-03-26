#include "gl.h"

GLVAO::GLVAO()
{
	glGenVertexArrays(1, &vao);
}

GLVAO::~GLVAO()
{
	for (int i = 0; i < vboList.size(); i++)
	{
		GLuint vbo = vboList[i];
		glDeleteBuffers(1, &vbo);
	}
	vboList.clear();

	if (vao != NULL)
	{
		glDeleteVertexArrays(1, &vao);
	}
}

int GLVAO::addVertx3D(float* data, int vertexCount, int layout)
{
	glBindVertexArray(vao);

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, vertexCount*3*sizeof(float), data, GL_STATIC_DRAW);
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(layout);
	vboList.push_back(vbo);

	glBindVertexArray(0);

	return 0;
}

int GLVAO::bindVAO()
{
	glBindVertexArray(vao);
	return 0;
}