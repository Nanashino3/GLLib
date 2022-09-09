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
// 関数名：Initialize
// 概　要：システムの初期化
// 引　数：なし
bool System::Initialize()
{
	// GLFWの初期化
	if (!glfwInit()) {
		std::cerr << "Can't initialize GLFW" << std::endl;
		return false;
	}

	// OpenGL Version 4.6 Core Profileを選択
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ウィンドウ画面作成
	mWindow = std::make_unique<Window>();

	// シェーダ関連の初期化
	mShader = std::make_unique<Shader>();
	mShader->Initialize(*mWindow.get());

	mShaderProgram = mShader->GetShaderProgram();

	mModelViewLoc = glGetUniformLocation(mShaderProgram, "modelView");
	mProjectionLoc = glGetUniformLocation(mShaderProgram, "projection");
	return true;
}

//********************************************************
// 関数名：ProcessMessage
// 概　要：システムの初期化
// 引　数：なし
bool System::ProcessMessage()
{
	// 入力処理の更新
	tkl::Input::Update(mWindow->GetWindow());
	return mWindow->IsWindowShouldClose();
}

//********************************************************
// 関数名：DoubleBuffering
// 概　要：ダブルバッファリング
// 引　数：なし
void System::DoubleBuffering() const
{
	mWindow->SwapBuffers();
}

//********************************************************
// 関数名：Finalize
// 概　要：システムの終了処理
// 引　数：なし
void System::Finalize()
{
	if(mRectagle != nullptr){ mRectagle = nullptr;}
	glfwTerminate();
}

// 2D四角形
int System::DrawBox(float posX, float posY, float width, float height, unsigned int color, int fillFlag)
{
	glUseProgram(mShaderProgram);

	if (mRectagle == nullptr) {
		Figure::Vertex vertices[] = {
			-1.0f,  1.0f, 0.0f,	// 左上
			 1.0f,  1.0f, 0.0f,	// 右上
			 1.0f, -1.0f, 0.0f,	// 右下
			-1.0f, -1.0f, 0.0f	// 左下
		};
		GLuint indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		GLsizei indicesNum= sizeof(indices) / sizeof(indices[0]);
		mRectagle = std::make_unique<Shape>(3, 4, vertices, indicesNum, indices);
	}

	//**********************************************
	// モデルビュー行列作成

	// モデル行列作成
	Matrix sm = Matrix::Scale(width, height, 0.0f);
	Matrix tm = Matrix::Translate(posX, -posY, 0.0f);
	Matrix mm = tm * sm;

	// モデルビュー行列
	Matrix vm = Matrix::Identity();
	Matrix mvm = vm * mm;

	GLint modelViewLoc = glGetUniformLocation(mShaderProgram, "modelView");
	glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, mvm.Data());
	//**********************************************

	//**********************************************
	// 射影行列作成
	const GLfloat* windowSize = mWindow->GetWindowSize();
	GLfloat w = windowSize[0] / 2.0f, h = windowSize[1] / 2.0f;
	Matrix pm = Matrix::OrthogonalProjection(-w, w, -h, h, 1.0f, -1.0f);

	GLint projectionLoc = glGetUniformLocation(mShaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, pm.Data());
	//**********************************************

	if(mRectagle != nullptr){ mRectagle->Draw(); }
	return 0;
}

// 3Dボックス
int System::DrawBox3D(float posX, float posY, float width, float height, unsigned int color, int fillFlag)
{
	glUseProgram(mShaderProgram);
	if (mRectagle == nullptr) {
		Figure::Vertex vertices[] = {
			{ -1.0f, -1.0f, -1.0f },	// 頂点0
			{ -1.0f, -1.0f,  1.0f },	// 頂点1
			{ -1.0f,  1.0f,  1.0f },	// 頂点2
			{ -1.0f,  1.0f, -1.0f },	// 頂点3
			{  1.0f,  1.0f, -1.0f },	// 頂点4
			{  1.0f, -1.0f, -1.0f },	// 頂点5
			{  1.0f, -1.0f,  1.0f },	// 頂点6
			{  1.0f,  1.0f,  1.0f }		// 頂点7
		};

		GLuint indices[] = {
			0, 1, 2, 0, 2, 3,	// 左
			3, 3, 4, 0, 4, 5,	// 裏
			0, 5, 6, 0, 6, 1,	// 下
			7, 6, 5, 7, 5, 4,	// 右
			7, 4, 3, 7, 3, 2,	// 上
			7, 2, 1, 7, 1, 6
		};
		GLsizei indicesNum = sizeof(indices) / sizeof(indices[0]);
		mRectagle = std::make_unique<Shape>(3, 8, vertices, indicesNum, indices);
	}

	//**********************************************
	// モデルビュー行列作成
	Matrix mm = Matrix::Translate(posX, -posY, 0.0f);
	Matrix vm = Matrix::LookAt(Vector3(3.0f, 4.0f, 5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	Matrix mvm = vm * mm;

	GLint modelViewLoc = glGetUniformLocation(mShaderProgram, "modelView");
	glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, mvm.Data());
	//**********************************************

	//**********************************************
	// 射影行列作成
	const GLfloat* windowSize = mWindow->GetWindowSize();
	GLfloat aspect = windowSize[0] / windowSize[1];
	Matrix pm = Matrix::PerspectiveProjection(90.0f, aspect, 1.0f, 10.0f);

	GLint projectionLoc = glGetUniformLocation(mShaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, pm.Data());
	//**********************************************

	if (mRectagle != nullptr) { mRectagle->Draw(); }
	return 0;
}