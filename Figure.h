#pragma once
#include <GL/glew.h>

// �}�`�N���X
class Figure
{
public:
	struct Vertex
	{
		GLfloat position[3];	// �ʒu
		GLfloat color[3];		// �F
	};

	Figure(GLint, GLsizei, const Vertex*, GLsizei indexCount = 0, const GLuint* index = 0);
	~Figure();

	void Bind() const;

private:
	Figure(const Figure&);
	Figure& operator=(const Figure&);

private:
	GLuint mVertexArray;	// ���_�z��I�u�W�F�N�g
	GLuint mVertexBuffer;	// ���_�o�b�t�@�I�u�W�F�N�g
	GLuint mIndexBuffer;	// ���_�o�b�t�@�I�u�W�F�N�g(�C���f�b�N�X)
};