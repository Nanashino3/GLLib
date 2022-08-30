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

	// �E�B���h�E�T�C�Y���擾
	const GLfloat* GetWindowSize() const { return mWindowSize; }
	// ���[���h���W�n�ɑ΂���f�o�C�X���W�n�̊g�嗦�����o��
	GLfloat GetScale() const { return mScale; }

private:
	GLFWwindow* const mWindow;
	GLfloat mWindowSize[2];		// �E�B���h�E�T�C�Y
	GLfloat mScale;				// ���[���h���W�n�ɑ΂���f�o�C�X���W�n�̊g�嗦
};