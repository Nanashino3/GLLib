#include "Shape.h"

Shape::Shape(GLint dimension, GLsizei vertexNum, const Figure::Vertex* vertex, GLsizei indexCount, const GLuint* index)
: mFigure(std::make_shared<const Figure>(dimension, vertexNum, vertex, indexCount, index))
, mVertexNum(vertexNum)
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
	glDrawArrays(GL_LINE_LOOP, 0, mVertexNum);
}
