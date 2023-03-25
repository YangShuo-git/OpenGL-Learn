#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "GL/gl.h"

using namespace std;

#define STRINGIZE(x)  #x
#define SHADER(shader) "" STRINGIZE(shader)

int main()
{
	cout << "Hello OpenGL!" << endl;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //TODO Core Profile

	int windowWidth = 1280;
	int windowHeight = 720;
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "OpenGLDemo", NULL, NULL);

	// OpenGL 运行模式--单线程
	// 多个线程同时调用不被允许
	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	char* vertexShader = SHADER(
		#version 330\n

		layout(location = 0) in vec3 pos;
		out vec3 outPos;

		void main()
		{
			outPos = pos;
			gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
		}
	);

	char* fragmentShader = SHADER(
		#version 330\n

		out vec4 rgbaColor;
		in vec3 outPos;

		void main()
		{
			rgbaColor = vec4(outPos, 1.0);
		}
		);

	//printf("vertexShader: %s/n", vertexShader);
	//GLShader* shader = new GLShader(shaderStr, GLShaderType::GL_SHADER_VERTEX);
	GLProgram* program = new GLProgram(vertexShader, fragmentShader);

	while (!glfwWindowShouldClose(window)) {
		//TODO 绘制操作

		// TODO 
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//delete shader;
	delete program;

	glfwTerminate();
	return 0;
}
