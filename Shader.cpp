#include "Shader.h"

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "Window.h"
#include "Matrix.h"

//********************************************************
// 関数名：PrintShaderInfoLog
// 概　要：シェーダオブジェクトのリンク結果を表示
// 引　数：第1引数[IN]　シェーダオブジェクト名
// 　　　　第2引数[IN]　表示する文字列
bool PrintShaderInfoLog(GLuint shader, const char* logStr)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE){
		std::cerr << "Compile Error in " << logStr << std::endl;
	}

	GLsizei bufSize;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);
	if(bufSize > 1){
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
		std::cerr << &infoLog[0] << std::endl;
	}

	return static_cast<bool>(status);
}

//********************************************************
// 関数名：PrintProgramInfoLog
// 概　要：プログラムオブジェクトのリンク結果を表示
// 引　数：第1引数[IN]　プログラムオブジェクト名
bool PrintProgramInfoLog(GLuint program)
{
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if(status == GL_FALSE){
		std::cerr << "Link Error." << std::endl;
	}

	GLsizei bufSize;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);
	if(bufSize > 1){
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
		std::cerr << &infoLog[0] << std::endl;
	}

	return static_cast<bool>(status);
}

//********************************************************
// 関数名：CreateShader
// 概　要：シェーダオブジェクトを作成
// 引　数：第1引数[IN]　頂点シェーダのソースプログラム
// 　　　　第2引数[IN]　画素シェーダのソースプログラム
unsigned int CreateShader(const char* vertexSrc, const char* fragmentSrc)
{
	const GLuint program = glCreateProgram();

	// 頂点シェーダオブジェクト
	if (vertexSrc != 0) {
		const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
		glCompileShader(vertexShader);

		if(PrintShaderInfoLog(vertexShader, "vertex shader")){
			glAttachShader(program, vertexShader);
		}
		glDeleteShader(vertexShader);
	}

	// 画素シェーダオブジェクト
	if (fragmentSrc != 0) {
		const GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragmentSrc, nullptr);
		glCompileShader(fragShader);

		if(PrintShaderInfoLog(fragShader, "fragment shader")){
			glAttachShader(program, fragShader);
		}
		glDeleteShader(fragShader);
	}

	// 各種属性をリンクする
	glBindAttribLocation(program, 0, "inPosition");
	glBindAttribLocation(program, 1, "inNormal");
	glBindFragDataLocation(program, 0, "outColor");
	glLinkProgram(program);

	if(PrintProgramInfoLog(program)){ return static_cast<unsigned int>(program); }

	glDeleteProgram(program);
	return 0;
}

//********************************************************
// 関数名：ReadShaderFile
// 概　要：シェーダファイルの読み込み
// 引　数：第1引数[IN]　 ファイル名
// 　　　　第2引数[OUT]　シェーダのソースプログラム
bool ReadShaderFile(const char* fileName, std::vector<GLchar>& buffer)
{
	if (fileName == 0) { return false; }

	std::ifstream file(fileName, std::ios::binary);
	if (file.fail()) {
		std::cerr << "Error：Can't open file." << fileName << std::endl;
		return false;
	}

	// ファイルサイズを取得
	file.seekg(0, std::ios::end);
	size_t length = file.tellg();

	// ファイルサイズ分のメモリ確保
	buffer.resize(length + 1);

	// ファイルの先頭からデータを読む
	file.seekg(0, std::ios::beg);
	file.read(buffer.data(), length);
	buffer[length] = '\0';

	if (file.fail()) {
		std::cerr << "Error：Could not read source file：" << fileName << std::endl;
		file.close();
		return false;
	}

	file.close();
	return true;
}

//********************************************************
// 関数名：Load2DShader
// 概　要：シェーダオブジェクトのロード(2D用)
// 引　数：第1引数[IN]　頂点シェーダのファイル名
// 　　　　第2引数[IN]　画素シェーダのファイル名
unsigned int Load2DShader(const char* vertexFile, const char* fragmentFile)
{
	std::vector<GLchar> vertexSrc;
	const bool vRet = ReadShaderFile(vertexFile, vertexSrc);
	std::vector<GLchar> fragmentSrc;
	const bool fRet = ReadShaderFile(fragmentFile, fragmentSrc);

	return (vRet && fRet) ? CreateShader(vertexSrc.data(), fragmentSrc.data()) : 0;
}

Shader::Shader()
: mShader(-1)
{}

Shader::~Shader()
{}

void Shader::Initialize(const Window& window)
{
//	mShader = Load2DShader("point.vert", "point.frag");
//	mShader = Load2DShader("LambertVert.glsl", "LambertFrag.glsl");
	mShader = Load2DShader("PhongVert.glsl", "PhongFrag.glsl");
	glUseProgram(mShader);
}

void Shader::SetMatrixUniform(const char* name, const Matrix& matrix)
{
	GLuint location = glGetUniformLocation(mShader, name);
	glUniformMatrix4fv(location, 1, GL_TRUE, matrix.Data());
}

void Shader::SetVectorUniform(const char* name, const Vector3& vector)
{
	GLuint location = glGetUniformLocation(mShader, name);
	glUniform3fv(location, 1, vector.GetAsFloatPtr());
}