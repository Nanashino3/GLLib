#pragma once
#include <memory>
#include "Figure.h"

class Shape
{
public:
	Shape(GLint, GLsizei, const Figure::Vertex*, GLsizei indexCount = 0, const GLuint* index = NULL);
	virtual ~Shape();

	void Draw() const;

private:
	virtual void Execute() const;

protected:
	const GLsizei mVertexNum;

private:
	std::shared_ptr<const Figure> mFigure;
};