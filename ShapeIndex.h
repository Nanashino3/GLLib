#pragma once
#include "Shape.h"

class ShapeIndex : public Shape
{
public:
	ShapeIndex(GLint, GLsizei, const Figure::Vertex*, GLsizei, const GLuint*);
	virtual ~ShapeIndex();

	virtual void Execute() const;

protected:
	const GLsizei mIndexNum;
};