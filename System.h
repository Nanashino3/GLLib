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

	// �}�`�`��֘A
	int DrawBox(float, float, float, float, unsigned int, int);

	// 3D�֘A�`��
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
	std::unique_ptr<Window> mWindow;	// �E�B���h�E�̃|�C���^
	std::unique_ptr<Shader> mShader;	// �V�F�[�_�̃|�C���^

	std::unique_ptr<Shape> mLine;		// ��
	std::unique_ptr<Shape> mRectagle;	// �l�p�p
	std::unique_ptr<Shape> mSphere;		// ��
	std::unique_ptr<Shape> mPlane;		// ����
	std::unique_ptr<Shape> mTexture;	// 2D�摜
	std::unique_ptr<Shape> mTexPlane;	// 3D�摜

	unsigned int mShaderProgram;		// �V�F�[�_���ʎq
	unsigned int mSimpleShaderProgram;	// �P���V�F�[�_���ʎq
	unsigned int mTexShaderProgram;

	Quaternion mRotation;
	Matrix mViewProjection;

	int mTextureW;
	int mTextureH;
	unsigned int mTextureID;
};