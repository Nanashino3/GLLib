#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int width = 1024, int height = 768, const char* title = "Hello");
	~Window();

	bool IsWindowShouldClose() const;
	void SwapBuffers() const;

	static void Resize(GLFWwindow* const, int, int);

	GLFWwindow* GetWindow() const { return mWindow; }
	const GLfloat* GetWindowSize() const { return mWindowSize; }
	GLfloat GetScale() const { return mScale; } 

private:
	GLFWwindow* const mWindow;
	GLfloat mWindowSize[2];		// ウィンドウサイズ
	GLfloat mScale;
};