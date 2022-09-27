#include "Shape.h"

Shape::Shape(GLint dimension, GLsizei vertexNum, const Figure::Vertex* vertex, GLsizei indexNum, const GLuint* index)
: mFigure(std::make_shared<const Figure>(dimension, vertexNum, vertex, indexNum, index))
, mVertexNum(vertexNum)
{}

Shape::~Shape()
{}

// 描画
void Shape::Draw() const
{
	// 頂点配列オブジェクトを結合する
	mFigure->Bind();
	// 描画開始
	Execute();
}

// 描画開始
void Shape::Execute() const
{
	glDrawArrays(GL_LINES, 0, mVertexNum);
}