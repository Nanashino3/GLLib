#include "ShapeIndex.h"

ShapeIndex::ShapeIndex(GLint dimension, GLsizei vertexNum, const Figure::Vertex* vertex, GLsizei indexNum, const GLuint* index)
: Shape(dimension, vertexNum, vertex, indexNum, index)
, mIndexNum(indexNum)
{}

ShapeIndex::~ShapeIndex()
{}

// •`‰æŠJŽn
void ShapeIndex::Execute() const
{
	glDrawElements(GL_TRIANGLES, mIndexNum, GL_UNSIGNED_INT, 0);
}