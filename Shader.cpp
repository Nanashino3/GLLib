#include "Shader.h"

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "Window.h"
#include "Matrix.h"

//********************************************************
// �֐����FPrintShaderInfoLog
// �T�@�v�F�V�F�[�_�I�u�W�F�N�g�̃����N���ʂ�\��
// ���@���F��1����[IN]�@�V�F�[�_�I�u�W�F�N�g��
// �@�@�@�@��2����[IN]�@�\�����镶����
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
// �֐����FPrintProgramInfoLog
// �T�@�v�F�v���O�����I�u�W�F�N�g�̃����N���ʂ�\��
// ���@���F��1����[IN]�@�v���O�����I�u�W�F�N�g��
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
// �֐����FCreateShader
// �T�@�v�F�V�F�[�_�I�u�W�F�N�g���쐬
// ���@���F��1����[IN]�@���_�V�F�[�_�̃\�[�X�v���O����
// �@�@�@�@��2����[IN]�@��f�V�F�[�_�̃\�[�X�v���O����
unsigned int CreateShader(const char* vertexSrc, const char* fragmentSrc)
{
	const GLuint program = glCreateProgram();

	// ���_�V�F�[�_�I�u�W�F�N�g
	if (vertexSrc != 0) {
		const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
		glCompileShader(vertexShader);

		if(PrintShaderInfoLog(vertexShader, "vertex shader")){
			glAttachShader(program, vertexShader);
		}
		glDeleteShader(vertexShader);
	}

	// ��f�V�F�[�_�I�u�W�F�N�g
	if (fragmentSrc != 0) {
		const GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragmentSrc, nullptr);
		glCompileShader(fragShader);

		if(PrintShaderInfoLog(fragShader, "fragment shader")){
			glAttachShader(program, fragShader);
		}
		glDeleteShader(fragShader);
	}

	// �e�푮���������N����
	glBindAttribLocation(program, 0, "inPosition");
	glBindAttribLocation(program, 1, "inNormal");
	glBindFragDataLocation(program, 0, "outColor");
	glLinkProgram(program);

	if(PrintProgramInfoLog(program)){ return static_cast<unsigned int>(program); }

	glDeleteProgram(program);
	return 0;
}

//********************************************************
// �֐����FReadShaderFile
// �T�@�v�F�V�F�[�_�t�@�C���̓ǂݍ���
// ���@���F��1����[IN]�@ �t�@�C����
// �@�@�@�@��2����[OUT]�@�V�F�[�_�̃\�[�X�v���O����
bool ReadShaderFile(const char* fileName, std::vector<GLchar>& buffer)
{
	if (fileName == 0) { return false; }

	std::ifstream file(fileName, std::ios::binary);
	if (file.fail()) {
		std::cerr << "Error�FCan't open file." << fileName << std::endl;
		return false;
	}

	// �t�@�C���T�C�Y���擾
	file.seekg(0, std::ios::end);
	size_t length = file.tellg();

	// �t�@�C���T�C�Y���̃������m��
	buffer.resize(length + 1);

	// �t�@�C���̐擪����f�[�^��ǂ�
	file.seekg(0, std::ios::beg);
	file.read(buffer.data(), length);
	buffer[length] = '\0';

	if (file.fail()) {
		std::cerr << "Error�FCould not read source file�F" << fileName << std::endl;
		file.close();
		return false;
	}

	file.close();
	return true;
}

//********************************************************
// �֐����FLoad2DShader
// �T�@�v�F�V�F�[�_�I�u�W�F�N�g�̃��[�h(2D�p)
// ���@���F��1����[IN]�@���_�V�F�[�_�̃t�@�C����
// �@�@�@�@��2����[IN]�@��f�V�F�[�_�̃t�@�C����
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