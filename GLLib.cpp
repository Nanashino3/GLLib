

#include "GLLib.h"

#include <iostream>
#include <fstream>
#include <vector>
#include "Shader.h"

GLFWwindow* gWindow = nullptr;
GLuint ShaderProgram = -1;

void ShaderInit()
{
	ShaderProgram = Shader::Load2DShader("point.vert", "point.frag");
}

bool GLLibInit()
{
	if (!glfwInit()) {
		std::cerr << "Can't initialize GLFW" << std::endl;
		return false;
	}

	GLFWwindow* const window = glfwCreateWindow(640, 480, "Hello", NULL, NULL);
	if(window == NULL){
		std::cerr << "Can't create GLFW window." << std::endl;
		return false;
	}
	gWindow = window;
	glfwMakeContextCurrent(window);

	const int version = gladLoadGL(glfwGetProcAddress);
	if (!version) {
		std::cerr << "" << std::endl;
		return false;
	}

	std::cout
		<< "Load OpenGLF"
		<< GLAD_VERSION_MAJOR(version)
		<< "."
		<< GLAD_VERSION_MINOR(version)
		<< std::endl;

	ShaderInit();

	return true;
}

void GLLibEnd()
{
	glfwTerminate();
}

bool ProcessMessage()
{
	return glfwWindowShouldClose(gWindow);
}

void SwapBuffers()
{
	glfwSwapBuffers(gWindow);
	glfwPollEvents();
}

int DrawBox(int fx, int fy, int ex, int ey, unsigned int color, int fillFlag)
{
	//glUseProgram(shaderProgram);
	return 0;
}