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

	// �}�`�`��֘A
	int DrawBox(float, float, float, float, unsigned int, int);
	int DrawBox3D(float, float, float, float, unsigned int, int);

private:
	System();
	System(const System&);
	System& operator=(const System&);

private:
	static System* sInstance;
	std::unique_ptr<Window> mWindow;	// �E�B���h�E�̃|�C���^
	std::unique_ptr<Shader> mShader;	// �V�F�[�_�̃|�C���^

	std::unique_ptr<Shape> mRectagle;	// �l�p�p

	unsigned int mModelViewLoc;
	unsigned int mProjectionLoc;
	unsigned int mShaderProgram;		// �V�F�[�_�I�u�W�F�N�g
};