#include "Shape.h"

Shape::Shape(GLint dimension, GLsizei vertexNum, const Figure::Vertex* vertex, GLsizei indexNum, const GLuint* index)
: mFigure(std::make_shared<const Figure>(dimension, vertexNum, vertex, indexNum, index))
, mVertexNum(vertexNum)
, mIndexNum(indexNum)
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
	glDrawElements(GL_TRIANGLES, mIndexNum, GL_UNSIGNED_INT, 0);
//	glDrawElements(GL_LINES, mIndexNum, GL_UNSIGNED_INT, 0);
}