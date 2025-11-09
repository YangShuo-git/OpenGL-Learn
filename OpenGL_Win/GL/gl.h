#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


enum GLShaderType
{
	GL_SHADER_VERTEX = 1,
	GL_SHADER_FRAGMENT,
};

class GLShader
{
public:
	GLShader(char* shaderStr, GLShaderType type);
	~GLShader();

public:
	GLuint shader = 0;
};

// ÔÚprogramÖÐ²Ù×÷shader
class GLProgram
{
public:
	GLProgram(char* vertexShaderStr, char* fragmentShaderSrc);
	~GLProgram();

	int useProgram();
	GLuint getProgram();

private:
	GLuint program = 0;
};

class GLVAO
{
public:
	GLVAO();
	~GLVAO();

	int addVertx3D(float* data, int vertexCount, int layout);

	int setIndex(unsigned int* indexData, int indexCount);

	int bindVAO();

	int draw();

private:
	GLuint vao = 0;
	GLuint ebo = 0;

	int drawTime = 0;

	std::vector<GLuint> vboList;
};

