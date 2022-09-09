#include "System.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Shader.h"
#include "Shape.h"
#include "Matrix.h"

#include "Input.h"

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

	mModelViewLoc = glGetUniformLocation(mShaderProgram, "modelView");
	mProjectionLoc = glGetUniformLocation(mShaderProgram, "projection");
	return true;
}

//********************************************************
// �֐����FProcessMessage
// �T�@�v�F�V�X�e���̏�����
// ���@���F�Ȃ�
bool System::ProcessMessage()
{
	// ���͏����̍X�V
	tkl::Input::Update(mWindow->GetWindow());
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

// 2D�l�p�`
int System::DrawBox(float posX, float posY, float width, float height, unsigned int color, int fillFlag)
{
	glUseProgram(mShaderProgram);

	if (mRectagle == nullptr) {
		Figure::Vertex vertices[] = {
			-1.0f,  1.0f, 0.0f,	// ����
			 1.0f,  1.0f, 0.0f,	// �E��
			 1.0f, -1.0f, 0.0f,	// �E��
			-1.0f, -1.0f, 0.0f	// ����
		};
		GLuint indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		GLsizei indicesNum= sizeof(indices) / sizeof(indices[0]);
		mRectagle = std::make_unique<Shape>(3, 4, vertices, indicesNum, indices);
	}

	//**********************************************
	// ���f���r���[�s��쐬

	// ���f���s��쐬
	Matrix sm = Matrix::Scale(width, height, 0.0f);
	Matrix tm = Matrix::Translate(posX, -posY, 0.0f);
	Matrix mm = tm * sm;

	// ���f���r���[�s��
	Matrix vm = Matrix::Identity();
	Matrix mvm = vm * mm;

	GLint modelViewLoc = glGetUniformLocation(mShaderProgram, "modelView");
	glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, mvm.Data());
	//**********************************************

	//**********************************************
	// �ˉe�s��쐬
	const GLfloat* windowSize = mWindow->GetWindowSize();
	GLfloat w = windowSize[0] / 2.0f, h = windowSize[1] / 2.0f;
	Matrix pm = Matrix::OrthogonalProjection(-w, w, -h, h, 1.0f, -1.0f);

	GLint projectionLoc = glGetUniformLocation(mShaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, pm.Data());
	//**********************************************

	if(mRectagle != nullptr){ mRectagle->Draw(); }
	return 0;
}

// 3D�{�b�N�X
int System::DrawBox3D(float posX, float posY, float width, float height, unsigned int color, int fillFlag)
{
	glUseProgram(mShaderProgram);
	if (mRectagle == nullptr) {
		Figure::Vertex vertices[] = {
			{ -1.0f, -1.0f, -1.0f },	// ���_0
			{ -1.0f, -1.0f,  1.0f },	// ���_1
			{ -1.0f,  1.0f,  1.0f },	// ���_2
			{ -1.0f,  1.0f, -1.0f },	// ���_3
			{  1.0f,  1.0f, -1.0f },	// ���_4
			{  1.0f, -1.0f, -1.0f },	// ���_5
			{  1.0f, -1.0f,  1.0f },	// ���_6
			{  1.0f,  1.0f,  1.0f }		// ���_7
		};

		GLuint indices[] = {
			0, 1, 2, 0, 2, 3,	// ��
			3, 3, 4, 0, 4, 5,	// ��
			0, 5, 6, 0, 6, 1,	// ��
			7, 6, 5, 7, 5, 4,	// �E
			7, 4, 3, 7, 3, 2,	// ��
			7, 2, 1, 7, 1, 6
		};
		GLsizei indicesNum = sizeof(indices) / sizeof(indices[0]);
		mRectagle = std::make_unique<Shape>(3, 8, vertices, indicesNum, indices);
	}

	//**********************************************
	// ���f���r���[�s��쐬
	Matrix mm = Matrix::Translate(posX, -posY, 0.0f);
	Matrix vm = Matrix::LookAt(Vector3(3.0f, 4.0f, 5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	Matrix mvm = vm * mm;

	GLint modelViewLoc = glGetUniformLocation(mShaderProgram, "modelView");
	glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, mvm.Data());
	//**********************************************

	//**********************************************
	// �ˉe�s��쐬
	const GLfloat* windowSize = mWindow->GetWindowSize();
	GLfloat aspect = windowSize[0] / windowSize[1];
	Matrix pm = Matrix::PerspectiveProjection(90.0f, aspect, 1.0f, 10.0f);

	GLint projectionLoc = glGetUniformLocation(mShaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, pm.Data());
	//**********************************************

	if (mRectagle != nullptr) { mRectagle->Draw(); }
	return 0;
}