#pragma once

class Window;
class Shader
{
public:
	Shader();
	~Shader();

	void Initialize(const Window&);

	unsigned int GetShaderProgram() const { return mShader; }

private:
	unsigned int mShader;
};