
#include "Figure.h"

Figure::Figure(GLint dimension, GLsizei vertexNum, const Vertex* vertex, GLsizei indexCount, const GLuint* index)
{
	// ���_�z��I�u�W�F�N�g
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	// ���_�o�b�t�@�I�u�W�F�N�g
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexNum * sizeof(Vertex), vertex, GL_STATIC_DRAW);

	// �C���f�b�N�X�̒��_�o�b�t�@�I�u�W�F�N�g
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), index, GL_STATIC_DRAW);

	// ��������Ă��钸�_�o�b�t�@�I�u�W�F�N�g��in�ϐ�����Q�Ƃł���悤�ɂ���
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, dimension, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->position);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, dimension, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->normal);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->uv);
}

Figure::~Figure()
{
	// ���_�o�b�t�@�I�u�W�F�N�g���폜����
	glDeleteBuffers(1, &mVertexBuffer);
	// �C���f�b�N�X�̒��_�o�b�t�@�I�u�W�F�N�g���폜����
	glDeleteBuffers(1, &mIndexBuffer);
	// ���_�z��I�u�W�F�N�g���폜����
	glDeleteVertexArrays(1, &mVertexArray);
}

// ���_�z��I�u�W�F�N�g�̌���
void Figure::Bind() const
{
	glBindVertexArray(mVertexArray);
}