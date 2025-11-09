#include "gl.h"
#include <stdlib.h>
#include <stdio.h>

GLProgram::GLProgram(char* vertexShaderStr, char* fragmentShaderSrc)
{
	program = glCreateProgram();

	GLShader vertexShader(vertexShaderStr, GLShaderType::GL_SHADER_VERTEX);
	GLShader fragmentShader(fragmentShaderSrc, GLShaderType::GL_SHADER_FRAGMENT);

	glAttachShader(program, vertexShader.shader);
	glAttachShader(program, fragmentShader.shader);

	glLinkProgram(program);

	GLint logLen = 0;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
	if (logLen > 0)
	{
		char* log = (char*)malloc(logLen);
		glGetProgramInfoLog(program, logLen, NULL, log);

		printf("Program Log:\n");
		printf("%s\n\n", log);

		free(log);
	}
}

GLProgram::~GLProgram()
{
	if (program != 0)
	{
		glDeleteProgram(program);
		program = 0;
	}
}

int GLProgram::useProgram()
{
	glUseProgram(program);
	return 0;
}

GLuint GLProgram::getProgram()
{
	return program;
}