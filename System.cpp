#include "System.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Shader.h"
#include "Shape.h"
#include "Matrix.h"

System* System::sInstance = nullptr;
System::System()
: mWindow(nullptr)
, mShaderProgram(-1)
{}

System* System::GetInstance()
{
	if(sInstance == nullptr){
		sInstance = new System();
	}
	return sInstance;
}
void System::DestroyInstance()
{
	delete sInstance;
}

//********************************************************
// �֐����FInitialize
// �T�@�v�F�V�X�e���̏�����
// ���@���F�Ȃ�
bool System::Initialize()
{
	// GLFW�̏�����
	if (!glfwInit()) {
		std::cerr << "Can't initialize GLFW" << std::endl;
		return false;
	}

	// OpenGL Version 4.6 Core Profile��I��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// �E�B���h�E��ʍ쐬
	mWindow = std::make_unique<Window>();

	// �V�F�[�_�֘A�̏�����
	mShader = std::make_unique<Shader>();
	mShader->Initialize(*mWindow.get());

	mShaderProgram = mShader->GetShaderProgram();

	mSizeLoc = glGetUniformLocation(mShaderProgram, "size");
	mScaleLoc = glGetUniformLocation(mShaderProgram, "scale");
	//mModelLoc = glGetUniformLocation(mShaderProgram, "worldTransform");

	return true;
}

//********************************************************
// �֐����FProcessMessage
// �T�@�v�F�V�X�e���̏�����
// ���@���F�Ȃ�
bool System::ProcessMessage()
{
	return mWindow->IsWindowShouldClose();
}

//********************************************************
// �֐����FDoubleBuffering
// �T�@�v�F�_�u���o�b�t�@�����O
// ���@���F�Ȃ�
void System::DoubleBuffering() const
{
	mWindow->SwapBuffers();
}

//********************************************************
// �֐����FFinalize
// �T�@�v�F�V�X�e���̏I������
// ���@���F�Ȃ�
void System::Finalize()
{
	if(mRectagle != nullptr){ mRectagle = nullptr;}
	glfwTerminate();
}

int System::DrawBox()
{
	glUseProgram(mShaderProgram);

	

	if(mRectagle == nullptr){
		Figure::Vertex points[] = {
			{ -0.5f, -0.5f },
			{  0.5f, -0.5f },
			{  0.5f,  0.5f },
			{ -0.5f,  0.5f }
		};
		mRectagle = std::make_unique<Shape>(2, 4, points);
	}

	glUniform2fv(mSizeLoc, 1, mWindow->GetWindowSize());
	glUniform1f(mScaleLoc, mWindow->GetScale());
	
	//const GLfloat* size = mWindow->GetWindowSize();
	//const GLfloat scale = mWindow->GetScale() * 2.0f;
	//const Matrix scaling = Matrix::Scale(scale / size[0], scale / size[1], 1.0f);

	//GLfloat x = 0.0 * 2.0f / size[0] - 1.0f;
	//GLfloat y = 1.0f - 0.0 * 2.0f / size[1];
	//const GLfloat const position[] = {x, y};
	//const Matrix translation = Matrix::Translate(position[0], position[1], 0.0f);

	//const Matrix worldTransform = translation * scaling;
	//glUniformMatrix4fv(mModelLoc, 1, GL_FALSE, worldTransform.Data());

	if(mRectagle != nullptr){
		mRectagle->Draw();
	}

	return 0;
}