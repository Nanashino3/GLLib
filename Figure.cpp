
#include "Figure.h"

Figure::Figure(GLint dimension, GLsizei vertexNum, const Vertex* vertex, GLsizei indexCount, const GLuint* index)
{
	// ���_�z��I�u�W�F�N�g
	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	// ���_�o�b�t�@�I�u�W�F�N�g
	glGenBuffers(1, &mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, vertexNum * sizeof(Vertex), vertex, GL_STATIC_DRAW);

	// �C���f�b�N�X�̒��_�o�b�t�@�I�u�W�F�N�g
	glGenBuffers(1, &mIbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), index, GL_STATIC_DRAW);

	// ��������Ă��钸�_�o�b�t�@�I�u�W�F�N�g��in�ϐ�����Q�Ƃł���悤�ɂ���
	glVertexAttribPointer(0, dimension, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->position);
	glEnableVertexAttribArray(0);
}

Figure::~Figure()
{
	// ���_�o�b�t�@�I�u�W�F�N�g���폜����
	glDeleteBuffers(1, &mVbo);
	// ���_�z��I�u�W�F�N�g���폜����
	glDeleteVertexArrays(1, &mVao);
	// �C���f�b�N�X�̒��_�o�b�t�@�I�u�W�F�N�g���폜����
	glDeleteBuffers(1, &mIbo);
}

// ���_�z��I�u�W�F�N�g�̌���
void Figure::Bind() const
{
	glBindVertexArray(mVao);
}