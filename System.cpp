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
	return true;
}

//********************************************************
// 関数名：ProcessMessage
// 概　要：システムの初期化
// 引　数：なし
bool System::ProcessMessage()
{
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

int System::DrawBox(int fx, int fy, int ex, int ey, unsigned int color, int fillFlag)
{
	glUseProgram(mShaderProgram);
	if(mRectagle == nullptr){
		Figure::Vertex points[] = { -0.5f,  0.5f, 0.5f,  0.5f, 0.5f, -0.5f, -0.5f, -0.5f };
		mRectagle = std::make_unique<Shape>(2, 4, points);
	}

	const GLfloat* size = mWindow->GetWindowSize();
	GLfloat temp[4][4] = {
		{ex, 0.0f, 0.0f, 0.0f},
		{0.0f, ey, 0.0f, 0.0f},
		{0.0f, 0.0, 1.0f, 0.0f},
		{fx - size[0] / 2.0f + ex / 2.0f, -fy + size[1] / 2.0f - ey / 2.0f, 0.0f, 1.0f}
	};
	GLuint worldTransformLoc = glGetUniformLocation(mShaderProgram, "worldTransform");
	glUniformMatrix4fv(worldTransformLoc, 1, GL_TRUE, *temp);

	if(mRectagle != nullptr){ mRectagle->Draw(); }
	return 0;
}