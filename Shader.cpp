
#include "Shader.h"

#include <iostream>
#include <fstream>
#include <vector>

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

GLuint CreateShader(const char* vertexSrc, const char* fragmentSrc)
{
	const GLuint program = glCreateProgram();

	// 頂点シェーダオブジェクト
	if (vertexSrc != NULL) {
		const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
		glCompileShader(vertexShader);

		if(PrintShaderInfoLog(vertexShader, "vertex shader")){
			glAttachShader(program, vertexShader);
		}
		glDeleteShader(vertexShader);
	}

	// 画素シェーダオブジェクト
	if (fragmentSrc != NULL) {
		const GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragmentSrc, nullptr);
		glCompileShader(fragShader);

		if(PrintShaderInfoLog(fragShader, "fragment shader")){
			glAttachShader(program, fragShader);
		}
		glDeleteShader(fragShader);
	}

	glLinkProgram(program);
	if(PrintProgramInfoLog(program)){ return program; }

	glDeleteProgram(program);
	return 0;
}


bool ReadShaderFile(const char* fileName, std::vector<GLchar>& buffer)
{
	if (fileName == NULL) { return false; }

	std::ifstream file(fileName, std::ios::binary);
	if (file.fail()) {
		std::cerr << "Error：Can't open file." << fileName << std::endl;
		return false;
	}

	// ファイルサイズを取得
	file.seekg(0, std::ios::end);
	int length = file.tellg();

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

GLuint Shader::Load2DShader(const char* vertexFile, const char* fragmentFile)
{
	std::vector<GLchar> vertexSrc;
	const bool vRet = ReadShaderFile(vertexFile, vertexSrc);
	std::vector<GLchar> fragmentSrc;
	const bool fRet = ReadShaderFile(fragmentFile, fragmentSrc);

	return (vRet && fRet) ? CreateShader(vertexSrc.data(), fragmentSrc.data()) : 0;
}