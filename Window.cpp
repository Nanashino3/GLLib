
#include "Window.h"
#include <iostream>

//********************************************************
// �֐����FWindow
// �T�@�v�F�R���X�g���N�^
// ���@���F�Ȃ�
Window::Window(int width, int height, const char* title)
: mWindow(glfwCreateWindow(width, height, title, 0, 0))
, mScale(100.0f)
{
	if (mWindow == 0) {
		std::cerr << "Can't create GLFW window." << std::endl;
		exit(1);
	}
	// ���݂̃E�B���h�E�������Ώۂɂ���
	glfwMakeContextCurrent(mWindow);

	// GLEW������������
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Can't initialize GLEW" << std::endl;
		exit(1);
	}

	// ���������̃^�C�~���O��҂�
	glfwSwapInterval(1);

	// this�|�C���^���L�^���Ă���
	glfwSetWindowUserPointer(mWindow, this);

	// �E�B���h�E�T�C�Y�̕ύX���ɌĂяo�������̓o�^
	glfwSetWindowSizeCallback(mWindow, Resize);

	Resize(mWindow, width, height);
}

//********************************************************
// �֐����F~Window
// �T�@�v�F�f�X�g���N�^
// ���@���F�Ȃ�
Window::~Window()
{
	glfwDestroyWindow(mWindow);
}

bool Window::IsWindowShouldClose() const
{
	return glfwWindowShouldClose(mWindow);
}

//********************************************************
// �֐����FSwapBuffers
// �T�@�v�F�V�F�[�_�I�u�W�F�N�g�̃��[�h(2D�p)
// ���@���F��1����[IN]�@���_�V�F�[�_�̃t�@�C����
// �@�@�@�@��2����[IN]�@��f�V�F�[�_�̃t�@�C����
void Window::SwapBuffers() const
{
	// �J���[�o�b�t�@�����ւ���
	glfwSwapBuffers(mWindow);

	// �C�x���g�����o��
	glfwPollEvents();
}


void Window::Resize(GLFWwindow* const window, int width, int height)
{
	// �t���[���o�b�t�@�T�C�Y���m�F
	int frameBufWidth, frameBufHeight;
	glfwGetFramebufferSize(window, &frameBufWidth, &frameBufHeight);

	// �t���[���o�b�t�@�S�̂��r���[�|�[�g�ɐݒ�
	glViewport(0, 0, frameBufWidth, frameBufHeight);

	Window* const instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if(instance != 0){
		instance->mWindowSize[0] = static_cast<GLfloat>(width);
		instance->mWindowSize[1] = static_cast<GLfloat>(height);
	}
}