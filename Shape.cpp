#include "Shape.h"

Shape::Shape(GLint dimension, GLsizei vertexNum, const Figure::Vertex* vertex, GLsizei indexCount, const GLuint* index)
: mFigure(std::make_shared<const Figure>(dimension, vertexNum, vertex, indexCount, index))
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
	// 折れ線で描画
	glDrawArrays(GL_LINE_LOOP, 0, mVertexNum);
}
