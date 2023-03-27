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

	// OpenGL 运行模式--单线程  多个线程同时调用不被允许
	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	char* vertexShader = SHADER(
		#version 330\n

		uniform float temp;

		layout(location = 0) in vec3 pos;
		out vec3 outPos;

		void main()
		{
			outPos = pos;
			float temp2 = sin(temp);
			gl_Position = vec4(pos.x* temp2, pos.y * temp2, pos.z * temp2, 1.0);
		}
	);

	char* fragmentShader = SHADER(
		#version 330\n

		out vec4 rgbaColor;
		in vec3 outPos;

		uniform sampler2D texture;

		void main()
		{
			rgbaColor = vec4(outPos, 1.0);
		}
	);

	// 3个顶点
	float vertex1[] =
	{
		0.0f,  1.0f,  0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f,  -1.0f, 0.0f,
	};

	// 4个顶点
	float vertex2[] =
	{
		-1.0f,  1.0f,  0.0f,  // 0
		1.0f,  1.0f, 0.0f,    // 1
		1.0f,  -1.0f, 0.0f,   // 2
		-1.0f, -1.0f, 0.0f,   // 3
	};

	// 两个三角形，顶点的顺序
	unsigned int index2[] =
	{
		0, 3, 1,
		1, 3, 2
	};

	GLVAO* vao = new GLVAO();
	vao->addVertx3D(vertex2, 4, 0);
	vao->setIndex(index2, 6);

	//printf("vertexShader: %s/n", vertexShader);
	//GLShader* shader = new GLShader(shaderStr, GLShaderType::GL_SHADER_VERTEX);
	GLProgram* program = new GLProgram(vertexShader, fragmentShader);

	// R G B    R G B    R G B    R G B
	// 以rgb的格式绘制一个2*2的图片
	int imgWidth = 2;
	int imgHeight = 2;
	unsigned char imgData[] =
	{
		255, 0, 0,     0, 255, 0,
		0, 0, 255,     127,127,127
	};

	GLuint textureId = 0;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNPACK_ALIGNMENT, imgData);

	float verValue = 0.5;
	while (!glfwWindowShouldClose(window)) {
		// 绘制操作
		glClear(GL_COLOR_BUFFER_BIT);

		program->useProgram();

		// 将verValue传递给shader中的变量temp
		GLint local = glGetUniformLocation(program->getProgram(), "temp");
		glUniform1f(local, verValue);

		// 纹理单元，只有通过纹理单元，才能传递texture
		GLint localTexture = glGetUniformLocation(program->getProgram(), "texture");
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glUniform1i(localTexture, 0);

		// 绘制三角形、矩形
		vao->draw();

		verValue += 0.001;

		// TODO 
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete vao;
	//delete shader;
	delete program;

	glfwTerminate();
	return 0;
}
