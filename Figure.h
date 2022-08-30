#pragma once
#include <GL/glew.h>

class Figure
{
public:
	struct Vertex
	{
		GLfloat position[2];	// �ʒu
	};

	Figure(GLint dimension, GLsizei vertexNum, const Vertex* vertex, GLsizei indexCount = 0, const GLuint* index = 0);
	~Figure();

	void Bind() const;

private:
	Figure(const Figure&);
	Figure& operator=(const Figure&);

private:
	GLuint mVao;	// ���_�z��I�u�W�F�N�g
	GLuint mVbo;	// ���_�o�b�t�@�I�u�W�F�N�g
	GLuint mIbo;	// ���_�o�b�t�@�I�u�W�F�N�g(�C���f�b�N�X)
};