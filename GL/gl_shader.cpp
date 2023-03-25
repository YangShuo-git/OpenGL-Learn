#include "gl.h"
#include <stdlib.h>
#include <stdio.h>

GLShader::GLShader(char* shaderStr, GLShaderType type)
{
	switch (type)
	{
	case GL_SHADER_VERTEX:
		shader = glCreateShader(GL_VERTEX_SHADER);
		break;
	case GL_SHADER_FRAGMENT:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		shader = glCreateShader(GL_VERTEX_SHADER);
		break;
	}

	GLint status;
	GLint logLen = 0;

	glShaderSource(shader, 1, &shaderStr, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
	if (logLen > 0)
	{
		char* log = (char*)malloc(logLen);
		glGetShaderInfoLog(shader, logLen, NULL, log);

		printf("Shader Log:\n");
		printf("%s\n", log);

		free(log);
	}
}

GLShader::~GLShader()
{
	if (shader != 0)
	{
		glDeleteShader(shader);
		shader = 0;
	}
}