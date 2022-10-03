#pragma once

#include <memory>
#include "Matrix.h"

namespace tkl{
	class Input;
}

class Window;
class Shader;
class Shape;

class System
{
public:
	static System* GetInstance();
	static void DestroyInstance();

	bool Initialize();
	bool ProcessMessage();
	void DoubleBuffering() const;
	void Finalize();

	// 図形描画関連
	int DrawBox(float, float, float, float, unsigned int, int);

	// 3D関連描画
	int DrawCube(float, float, float, float, float, float, unsigned int, int);
	int DrawSphere(float, float, float, float, int, int);
	int DrawPlane(float, float, float, float, float, float, unsigned int, int);

	void DirectionalLight();
	void DrawGridGround(float, int, unsigned int);

	int LoadGraph(const char*);
	void DrawGraph(float, float);
	void DrawGraphPlane(float, float, float);

	void SetViewProjection(const Matrix& vpm){ mViewProjection = vpm; }

private:
	System();
	System(const System&);
	System& operator=(const System&);

private:
	static System* sInstance;
	std::unique_ptr<Window> mWindow;	// ウィンドウのポインタ
	std::unique_ptr<Shader> mShader;	// シェーダのポインタ

	std::unique_ptr<Shape> mLine;		// 線
	std::unique_ptr<Shape> mRectagle;	// 四角用
	std::unique_ptr<Shape> mSphere;		// 球
	std::unique_ptr<Shape> mPlane;		// 平面
	std::unique_ptr<Shape> mTexture;	// 2D画像
	std::unique_ptr<Shape> mTexPlane;	// 3D画像

	unsigned int mShaderProgram;		// シェーダ識別子
	unsigned int mSimpleShaderProgram;	// 単純シェーダ識別子
	unsigned int mTexShaderProgram;

	Quaternion mRotation;
	Matrix mViewProjection;

	int mTextureW;
	int mTextureH;
	unsigned int mTextureID;
};