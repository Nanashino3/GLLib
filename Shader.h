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
	void SetMatrixUniform(const char*, const Matrix&);
	void SetVectorUniform(const char*, const Vector3&);

private:
	unsigned int mShader;
};