#pragma once

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

public:
	GLuint program = 0;
};