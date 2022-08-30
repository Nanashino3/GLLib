#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int width = 640, int height = 480, const char* title = "Hello");
	~Window();

	bool IsWindowShouldClose() const;
	void SwapBuffers() const;

	static void Resize(GLFWwindow* const, int, int);

	// ウィンドウサイズを取得
	const GLfloat* GetWindowSize() const { return mWindowSize; }
	// ワールド座標系に対するデバイス座標系の拡大率を取り出す
	GLfloat GetScale() const { return mScale; }

private:
	GLFWwindow* const mWindow;
	GLfloat mWindowSize[2];		// ウィンドウサイズ
	GLfloat mScale;				// ワールド座標系に対するデバイス座標系の拡大率
};