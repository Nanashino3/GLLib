#pragma once

class Window;
class Matrix;
class Vector3;

class Shader
{
public:
	Shader();
	~Shader();

	void Initialize(const Window&);

	unsigned int GetShaderProgram() const { return mShader; }
	unsigned int GetSimpleShaderProgram() const { return mSimpleShader; }
	unsigned int GetTexShaderProgram() const { return mTexShader; }
	void SetMatrixUniform(const char*, const Matrix&);
	void SetVectorUniform(const char*, const Vector3&);

private:
	unsigned int mShader;
	unsigned int mSimpleShader;
	unsigned int mTexShader;
};