#include "System.h"

#include <iostream>
#include <iomanip>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

#include "Window.h"
#include "Shader.h"
#include "ShapeIndex.h"
#include "Matrix.h"

#include "Input.h"

System* System::sInstance = nullptr;
System::System()
: mWindow(nullptr)
, mShaderProgram(-1)
, mSimpleShaderProgram(-1)
, mRotation(Quaternion())
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
	mSimpleShaderProgram = mShader->GetSimpleShaderProgram();
	mTexShaderProgram = mShader->GetTexShaderProgram();

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
	glUseProgram(mSimpleShaderProgram);

	if (mRectagle == nullptr) {
		Figure::Vertex vertices[] = {
			{ -0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f}, // 左上
			{  0.5f,  0.5f,  0.0f,	1.0f,  0.0f,  0.0f}, // 右上
			{  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f}, // 右下
			{ -0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f}	 // 左下
		};
		GLuint indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		GLsizei indicesNum= sizeof(indices) / sizeof(indices[0]);
		mRectagle = std::make_unique<ShapeIndex>(3, 4, vertices, indicesNum, indices);
	}
	
	//**********************************************
	// ワールド変換行列作成
	Matrix wm = Matrix::Translate(posX, -posY, 0.0f);
	wm *= Matrix::Scale(width, height, 0.0f);

	GLint modelViewLoc = glGetUniformLocation(mSimpleShaderProgram, "uWorldTransform");
	glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, wm.Data());
	//**********************************************

	//**********************************************
	// ビュー射影行列の作成
	const GLfloat* windowSize = mWindow->GetWindowSize();
	GLfloat w = windowSize[0] / 2.0f, h = windowSize[1] / 2.0f;
	Matrix vpm = Matrix::OrthogonalProjection(-w, w, -h, h, 1.0f, -1.0f);

	GLint projectionLoc = glGetUniformLocation(mSimpleShaderProgram, "uViewProjection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, vpm.Data());
	//**********************************************

	if(mRectagle != nullptr){ mRectagle->Draw(); }
	
	return 0;
}

// 3Dボックス
int System::DrawCube(float posX, float posY, float posZ, float width, float height, float depth, unsigned int color, int fillFlag)
{
	glUseProgram(mShaderProgram);
	if (mRectagle == nullptr) {
		Figure::Vertex vertices[] = {
			// 左面
			{ -1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f },
			{ -1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f },
			{ -1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f },
			{ -1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f },
			
			// 裏面
			{  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f },
			{ -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f },
			{ -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f },
			{  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f },

			// 下面
			{ -1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  0.0f },
			{  1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  0.0f },
			{  1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f },
			{ -1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f },

			// 右面
			{  1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f },
			{  1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f },
			{  1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f },
			{  1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f },

			// 上面
			{ -1.0f,  1.0f, -1.0f,  0.0f, -1.0f,  0.0f },
			{ -1.0f,  1.0f,  1.0f,  0.0f, -1.0f,  0.0f },
			{  1.0f,  1.0f,  1.0f,  0.0f, -1.0f,  0.0f },
			{  1.0f,  1.0f, -1.0f,  0.0f, -1.0f,  0.0f },

			// 前面
			{ -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, -1.0f },
			{  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, -1.0f },
			{  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f },
			{ -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f }
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
		mRectagle = std::make_unique<ShapeIndex>(3, 24, vertices, indicesNum, indices);
	}

	//**********************************************
	// ワールド変換行列作成(右手座標形なので「平行→回転→拡縮」の順)
//	mRotation *= Quaternion::AngleAxis(Vector3(1.0f, 0.0f, 0.0f), ToRadian(1.0f));	// X軸回転

	Matrix wm = Matrix::Translate(posX, -posY, posZ);
	wm *= Matrix::CreateQuaternion(mRotation);
	wm *= Matrix::Scale(width, height, depth);

	GLint worldTransformLoc = glGetUniformLocation(mShaderProgram, "uWorldTransform");
	glUniformMatrix4fv(worldTransformLoc, 1, GL_FALSE, wm.Data());

	//**********************************************
	// ビュー射影行列作成
	GLint viewProjectionLoc = glGetUniformLocation(mShaderProgram, "uViewProjection");
	glUniformMatrix4fv(viewProjectionLoc, 1, GL_FALSE, mViewProjection.Data());

	if (mRectagle != nullptr) { mRectagle->Draw(); }
	return 0;
}

// 球
int System::DrawSphere(float posX, float posY, float posZ, float radius, int divWidth, int divHeight)
{
	glUseProgram(mShaderProgram);
	if(mSphere == nullptr){
		std::vector<Figure::Vertex> sphereVertex;
		// 頂点座標計算
		for(int i = 0; i < (divHeight + 1); ++i){
			float t = static_cast<float>(i) / static_cast<float>(divHeight);
			float y = std::cosf(PI * t) * radius;		// 高さ
			float r = std::sinf(PI * t) * radius;		// 半径

			for(int j = 0; j < (divWidth + 1); ++j){
				float s = static_cast<float>(j) / static_cast<float>(divWidth);
				float x = r * std::cosf(2 * PI * s);	// 横幅
				float z = r * std::sinf(2 * PI * s);	// 奥行き

				// 頂点座標を登録
				Figure::Vertex vertex = {x, y, z, x, y, z};
				sphereVertex.emplace_back(vertex);
			}
		}

		// インデックス計算
		std::vector<GLuint> sphereIndex;
		for(int i = 0; i < (divHeight + 1); ++i){
			for(int j = 0; j < (divWidth + 1); ++j){
				int v0 = (divWidth + 1) * i + j;	// 左上
				int v1 = v0 + 1;					// 右上
				int v2 = v1 + divWidth;				// 左下
				int v3 = v2 + 1;					// 右下

				// 左下の三角形
				sphereIndex.emplace_back(v0);
				sphereIndex.emplace_back(v2);
				sphereIndex.emplace_back(v3);

				// 右上の三角形
				sphereIndex.emplace_back(v0);
				sphereIndex.emplace_back(v3);
				sphereIndex.emplace_back(v1);
			}
		}


		mSphere = std::make_unique<ShapeIndex>(3,
			static_cast<GLsizei>(sphereVertex.size()), sphereVertex.data(),
			static_cast<GLsizei>(sphereIndex.size()), sphereIndex.data());
	}

	Vector3 camPos = Vector3(3.0f, 4.0f, 5.0f);

	//**********************************************
	// ワールド変換行列作成

	Matrix wm = Matrix::Translate(posX, -posY, posZ);
	wm *= Matrix::Rotate(static_cast<GLfloat>(glfwGetTime()), Vector3(0.0f, 1.0f, 0.0f));

	GLint modelViewLoc = glGetUniformLocation(mShaderProgram, "uWorldTransform");
	glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, wm.Data());
	//**********************************************

	//**********************************************
	// ビュー射影行列作成
	GLint projectionLoc = glGetUniformLocation(mShaderProgram, "uViewProjection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, mViewProjection.Data());

	if(mSphere != nullptr){ mSphere->Draw(); }

	return 0;
}

// 3D平面
int System::DrawPlane(float posX, float posY, float posZ, float width, float height, float depth, unsigned int color, int fillFlag)
{
	glUseProgram(mShaderProgram);
	if(mPlane == nullptr){
		Figure::Vertex vertices[] = {
			{-1.0,  0.0f, -1.0f,  0.0f, -1.0f, 0.0f},
			{ 1.0,  0.0f, -1.0f,  0.0f, -1.0f, 0.0f},
			{ 1.0,  0.0f,  1.0f,  0.0f, -1.0f, 0.0f},
			{-1.0,  0.0f,  1.0f,  0.0f, -1.0f, 0.0f}
		};

		GLuint indices[] = {
			0, 1, 2,
			0, 2, 3
		};
		
		GLsizei indexNum = sizeof(indices) / sizeof(indices[0]);
		mPlane = std::make_unique<ShapeIndex>(3, 4, vertices, indexNum, indices);
	}

	//**********************************************
	// ワールド変換行列作成
	Matrix wm = Matrix::Translate(posX, -posY, posZ);

	GLint modelViewLoc = glGetUniformLocation(mShaderProgram, "uWorldTransform");
	glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, wm.Data());
	//**********************************************

	//**********************************************
	// ビュー射影行列作成
	GLint projectionLoc = glGetUniformLocation(mShaderProgram, "uViewProjection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, mViewProjection.Data());

	if(mPlane != nullptr){ mPlane->Draw(); }
	return 0;
}

// 平行光源(TOOD：決め打ち)
void System::DirectionalLight()
{
	Vector3 camPos = Vector3(0.0f, 1.0f, 0.0f);

	//**********************************************
	// 光源設定
	// ライティングパラメータ設定
	Vector3 ambientLight = Vector3(0.2f, 0.2f, 0.2f);
	Vector3 dirLightDirection = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 dirLightDiffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 dirLightSpecColor = Vector3(0.8f, 0.8f, 0.8f);

	GLuint camPosLoc = glGetUniformLocation(mShaderProgram, "uCameraPos");
	glUniform3fv(camPosLoc, 1, camPos.GetAsFloatPtr());

	GLuint ambentLightLoc = glGetUniformLocation(mShaderProgram, "uAmbientColor");
	glUniform3fv(ambentLightLoc, 1, ambientLight.GetAsFloatPtr());

	GLuint lightDirLoc = glGetUniformLocation(mShaderProgram, "uDirLight.mDirection");
	glUniform3fv(lightDirLoc, 1, dirLightDirection.GetAsFloatPtr());

	GLuint lightDiffuseLoc = glGetUniformLocation(mShaderProgram, "uDirLight.mDiffuseColor");
	glUniform3fv(lightDiffuseLoc, 1, dirLightDiffuseColor.GetAsFloatPtr());

	GLuint lightSpecLoc = glGetUniformLocation(mShaderProgram, "uDirLight.mSpecColor");
	glUniform3fv(lightSpecLoc, 1, dirLightSpecColor.GetAsFloatPtr());

	GLuint specPowerLoc = glGetUniformLocation(mShaderProgram, "uSpecPower");
	glUniform1f(specPowerLoc, 2.0f);

	//**********************************************
}

// グリッド
void System::DrawGridGround(float size, int rowNum, unsigned int color)
{
	glUseProgram(mSimpleShaderProgram);
	if(mLine == nullptr){
		float l = rowNum * 0.5f;
		float n = -l;

		Figure::Vertex v[4] = {0.0f}; 
		std::vector<Figure::Vertex> gridVertex;

		for(int i = 0; i < rowNum + 1; ++i){
			if((rowNum >> 1) == i){
				v[0] = {  n,  0,  l,  1.0f,  0.0f,  0.0f };
				v[1] = {  n,  0, -l,  1.0f,  0.0f,  0.0f };
				v[2] = {  l,  0,  n,  0.0f,  0.0f,  1.0f };
				v[3] = { -l,  0,  n,  0.0f,  0.0f,  1.0f };
			}else{
				v[0] = {  n,  0,  l,  1.0f,  1.0f,  1.0f };
				v[1] = {  n,  0, -l,  1.0f,  1.0f,  1.0f };
				v[2] = {  l,  0,  n,  1.0f,  1.0f,  1.0f };
				v[3] = { -l,  0,  n,  1.0f,  1.0f,  1.0f };
			}

			gridVertex.emplace_back(v[0]);
			gridVertex.emplace_back(v[1]);
			gridVertex.emplace_back(v[2]);
			gridVertex.emplace_back(v[3]);

			n += 1.0f;
		}

		Figure::Vertex v5 = { 0.0f,   l,  0.0f,  0.0f,  1.0f,  0.0f };
		Figure::Vertex v6 = { 0.0f,  -l,  0.0f,  0.0f,  1.0f,  0.0f };

		gridVertex.emplace_back(v5);
		gridVertex.emplace_back(v6);
		mLine = std::make_unique<Shape>(3,
			gridVertex.size(), gridVertex.data());
	}

	//**********************************************
	// ワールド変換行列作成
	Matrix wm = Matrix::Translate(0.0f, 0.0f, 0.0f);
	GLint modelViewLoc = glGetUniformLocation(mSimpleShaderProgram, "uWorldTransform");
	glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, wm.Data());
	//**********************************************

	//**********************************************
	// ビュー射影行列作成
	GLint projectionLoc = glGetUniformLocation(mSimpleShaderProgram, "uViewProjection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, mViewProjection.Data());

	if(mLine != nullptr){ mLine->Draw(); }
}

// 画像の読み込み
int System::LoadGraph(const char* name)
{
	int channels = 0;
	unsigned char* image = SOIL_load_image(name, &mTextureW, &mTextureH, &channels, SOIL_LOAD_AUTO);

	if (image == nullptr) { return -1; }

	int format = (channels == 4) ? GL_RGBA : GL_RGB;

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, format, mTextureW, mTextureH, 0, format, GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return 0;
}

void System::DrawGraph(float posX, float posY)
{
	glUseProgram(mTexShaderProgram);
	if(mTexture == nullptr){
		Figure::Vertex vertices[] = {
			{-0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f,  0.0f},
			{ 0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f,  0.0f},
			{ 0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f,  1.0f},
			{-0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f,  1.0f}
		};

		GLuint indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLsizei indicesNum = sizeof(indices) / sizeof(indices[0]);
		mTexture = std::make_unique<ShapeIndex>(3, 4, vertices, indicesNum, indices);
	}
	//**********************************************
	// ワールド変換行列作成
	Matrix wm = Matrix::Translate(posX, -posY, 0.0f);
	wm *= Matrix::Scale(mTextureW, mTextureH, 1.0f);

	GLint modelViewLoc = glGetUniformLocation(mTexShaderProgram, "uWorldTransform");
	glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, wm.Data());

	//**********************************************
	// ビュー射影行列作成
	const GLfloat* windowSize = mWindow->GetWindowSize();
	GLfloat w = windowSize[0] / 2.0f, h = windowSize[1] / 2.0f;
	Matrix vpm = Matrix::OrthogonalProjection(-w, w, -h, h, 1.0f, -1.0f);

	GLint projectionLoc = glGetUniformLocation(mTexShaderProgram, "uViewProjection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, vpm.Data());

	if(mTexture != nullptr){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, mTextureID);
		mTexture->Draw();
	}

}

void System::DrawGraphPlane(float posX, float posY, float posZ)
{
	glUseProgram(mShaderProgram);
	if(mTexPlane == nullptr){
		Figure::Vertex vertices[] = {
			{-1.0,  0.0f, -1.0f,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f},
			{ 1.0,  0.0f, -1.0f,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f},
			{ 1.0,  0.0f,  1.0f,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f},
			{-1.0,  0.0f,  1.0f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f}
		};

		GLuint indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLsizei indexNum = sizeof(indices) / sizeof(indices[0]);
		mTexPlane = std::make_unique<ShapeIndex>(3, 4, vertices, indexNum, indices);
	}
	//**********************************************
	// ワールド変換行列作成
	Matrix wm = Matrix::Translate(posX, -posY, posZ);

	GLint modelViewLoc = glGetUniformLocation(mShaderProgram, "uWorldTransform");
	glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, wm.Data());
	//**********************************************

	//**********************************************
	// ビュー射影行列作成
	GLint projectionLoc = glGetUniformLocation(mShaderProgram, "uViewProjection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, mViewProjection.Data());

	if(mTexPlane != nullptr){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, mTextureID); 
		mTexPlane->Draw();
	}
	
	return;
}