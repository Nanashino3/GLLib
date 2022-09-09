#include "Shape.h"

Shape::Shape(GLint dimension, GLsizei vertexNum, const Figure::Vertex* vertex, GLsizei indexNum, const GLuint* index)
: mFigure(std::make_shared<const Figure>(dimension, vertexNum, vertex, indexNum, index))
, mVertexNum(vertexNum)
, mIndexNum(indexNum)
{}

Shape::~Shape()
{}

// �`��
void Shape::Draw() const
{
	// ���_�z��I�u�W�F�N�g����������
	mFigure->Bind();
	// �`��J�n
	Execute();
}

// �`��J�n
void Shape::Execute() const
{
	// �܂���ŕ`��
	glDrawElements(GL_TRIANGLES, mIndexNum, GL_UNSIGNED_INT, 0);
//	glDrawElements(GL_LINES, mIndexNum, GL_UNSIGNED_INT, 0);
}