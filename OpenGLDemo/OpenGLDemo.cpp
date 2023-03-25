#include "OpenGLDemo.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"

using namespace std;

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

	while (!glfwWindowShouldClose(window)) {
		//TODO 绘制操作

		// TODO 
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
