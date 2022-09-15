#pragma once

#include <memory>

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
	int DrawCube(float, float, float, float, float, unsigned int, int);
	int DrawSphere(float, int, int);

private:
	System();
	System(const System&);
	System& operator=(const System&);

private:
	static System* sInstance;
	std::unique_ptr<Window> mWindow;	// ウィンドウのポインタ
	std::unique_ptr<Shader> mShader;	// シェーダのポインタ

	std::unique_ptr<Shape> mRectagle;	// 四角用
	std::unique_ptr<Shape> mSphere;		// 球

	unsigned int mModelViewLoc;
	unsigned int mProjectionLoc;
	unsigned int mShaderProgram;		// シェーダオブジェクト
};