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

	// タイマーの初期化
	glfwSetTime(0.0f);

	// ウィンドウ画面作成
	mWindow = std::make_unique<Window>();

	// デプスバッファ(Zバッファ)を有効にする
	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

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
			{ -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f}, // 左上
			{  1.0f,  1.0f,  0.0f,	1.0f,  0.0f,  0.0f}, // 右上
			{  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f}, // 右下
			{ -1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f}	 // 左下
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
int System::DrawCube(float posX, float posY, float posZ, float width, float height, unsigned int color, int fillFlag)
{
	glUseProgram(mShaderProgram);
	if (mRectagle == nullptr) {
		Figure::Vertex vertices[] = {
			// 左面
			{ -1.0f, -1.0f, -1.0f, 0.1f, 0.8f, 0.1f },
			{ -1.0f, -1.0f,  1.0f, 0.1f, 0.8f, 0.1f },
			{ -1.0f,  1.0f,  1.0f, 0.1f, 0.8f, 0.1f },
			{ -1.0f,  1.0f, -1.0f, 0.1f, 0.8f, 0.1f },
			
			// 裏面
			{  1.0f, -1.0f, -1.0f, 0.8f, 0.1f, 0.8f },
			{ -1.0f, -1.0f, -1.0f, 0.8f, 0.1f, 0.8f },
			{ -1.0f,  1.0f, -1.0f, 0.8f, 0.1f, 0.8f },
			{  1.0f,  1.0f, -1.0f, 0.8f, 0.1f, 0.8f },

			// 下面
			{ -1.0f, -1.0f, -1.0f, 0.1f, 0.8f, 0.8f },
			{  1.0f, -1.0f, -1.0f, 0.1f, 0.8f, 0.8f },
			{  1.0f, -1.0f,  1.0f, 0.1f, 0.8f, 0.8f },
			{ -1.0f, -1.0f,  1.0f, 0.1f, 0.8f, 0.8f },

			// 右面
			{  1.0f, -1.0f,  1.0f, 0.1f, 0.1f, 0.8f },
			{  1.0f, -1.0f, -1.0f, 0.1f, 0.1f, 0.8f },
			{  1.0f,  1.0f, -1.0f, 0.1f, 0.1f, 0.8f },
			{  1.0f,  1.0f,  1.0f, 0.1f, 0.1f, 0.8f },

			// 上面
			{ -1.0f,  1.0f, -1.0f, 0.8f, 0.1f, 0.1f },
			{ -1.0f,  1.0f,  1.0f, 0.8f, 0.1f, 0.1f },
			{  1.0f,  1.0f,  1.0f, 0.8f, 0.1f, 0.1f },
			{  1.0f,  1.0f, -1.0f, 0.8f, 0.1f, 0.1f },

			// 前面
			{ -1.0f, -1.0f,  1.0f, 0.8f, 0.8f, 0.1f },
			{  1.0f, -1.0f,  1.0f, 0.8f, 0.8f, 0.1f },
			{  1.0f,  1.0f,  1.0f, 0.8f, 0.8f, 0.1f },
			{ -1.0f,  1.0f,  1.0f, 0.8f, 0.8f, 0.1f }
		};

		GLuint indices[] = {
			 0,  1,  2,  0,  2,  3,	// 左面
			 4,  5,  6,  4,  6,  7,	// 裏面
			 8,  9, 10,  8, 10, 11,	// 下面
			12, 13, 14, 12, 14, 15,	// 右面
			16, 17, 18, 16, 18, 19,	// 上面
			20, 21, 22, 20, 22, 23	// 前面
		};

		// 背面カリングを有効にする
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);

		GLsizei indicesNum = sizeof(indices) / sizeof(indices[0]);
		mRectagle = std::make_unique<Shape>(3, 24, vertices, indicesNum, indices);
	}

	//**********************************************
	// モデルビュー行列作成
	
	Matrix rm = Matrix::Rotate(static_cast<GLfloat>(glfwGetTime()), Vector3(0.0f, 1.0f, 0.0f));

	Matrix mm = rm * Matrix::Translate(posX, -posY, posZ);
	Matrix vm = Matrix::LookAt(Vector3(3.0f, 4.0f, 5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	Matrix mvm = vm * mm;

	GLint modelViewLoc = glGetUniformLocation(mShaderProgram, "modelView");
	glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, mvm.Data());
	//**********************************************

	//**********************************************
	// 射影行列作成
	const GLfloat* windowSize = mWindow->GetWindowSize();
	GLfloat aspect = windowSize[0] / windowSize[1];
	Matrix pm = Matrix::PerspectiveProjection(90.0f, aspect, 1.0f, -1.0f);

	GLint projectionLoc = glGetUniformLocation(mShaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, pm.Data());
	//**********************************************

	if (mRectagle != nullptr) { mRectagle->Draw(); }
	return 0;
}

// 球
int System::DrawSphere(float radius, int divWidth, int divHeight)
{
	glUseProgram(mShaderProgram);
	
	if(mSphere == nullptr){
		// 球の分割数
		const int slices = 16, stacks = 8;
		std::vector<Figure::Vertex> solidSphereVertex;
		for (int j = 0; j <= stacks; ++j) {

			// y = cos(πt);
			// r = sin(πt);
			const float t = static_cast<float>(j) / static_cast<float>(stacks);
			const float y = std::cosf(PI * t), r = std::sinf(PI * t);

			for (int i = 0; i <= slices; ++i) {
				// z = r * cos(2πt);
				// x = r * sin(2πt);
				const float s = static_cast<float>(i) / static_cast<float>(slices);
				const float z = r * std::cosf(2 * PI * s), x = r * std::sinf(2 * PI * s);

				// 頂点座標
				const Figure::Vertex vertex = { x, y, z, x, y, z };
				solidSphereVertex.emplace_back(vertex);
			}
		}

		// インデックスを作成
		std::vector<GLuint> solidSphereIndex;
		for (int j = 0; j < stacks; ++j) {
			const int k = (slices + 1) * j;
			for (int i = 0; i < slices; ++i) {
				// 頂点インデックス
				const GLuint k0 = k + i;
				const GLuint k1 = k0 + 1;
				const GLuint k2 = k1 + slices;
				const GLuint k3 = k2 + 1;

				// 左下の三角形
				solidSphereIndex.emplace_back(k0);
				solidSphereIndex.emplace_back(k2);
				solidSphereIndex.emplace_back(k3);

				// 右下の三角形
				solidSphereIndex.emplace_back(k0);
				solidSphereIndex.emplace_back(k3);
				solidSphereIndex.emplace_back(k1);
			}
		}

		mSphere = std::make_unique<Shape>(3, 
										  static_cast<GLsizei>(solidSphereVertex.size()), solidSphereVertex.data(),
										  static_cast<GLsizei>(solidSphereIndex.size()), solidSphereIndex.data());

	}

	//**********************************************
	// モデルビュー行列作成
	Matrix rm = Matrix::Rotate(static_cast<GLfloat>(glfwGetTime()), Vector3(0.0f, 1.0f, 0.0f));

	Matrix mm = rm * Matrix::Translate(0, 0, 0);
	Matrix vm = Matrix::LookAt(Vector3(0.0f, 0.0f, 5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	Matrix mvm = vm * mm;

	GLint modelViewLoc = glGetUniformLocation(mShaderProgram, "modelView");
	glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, mvm.Data());
	//**********************************************

	//**********************************************
	// 射影行列作成
	const GLfloat* windowSize = mWindow->GetWindowSize();
	GLfloat aspect = windowSize[0] / windowSize[1];
	Matrix pm = Matrix::PerspectiveProjection(60.0f, aspect, 1.0f, -1.0f);

	GLint projectionLoc = glGetUniformLocation(mShaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, pm.Data());
	//**********************************************

	if(mSphere != nullptr){ mSphere->Draw(); }

	return 0;
}