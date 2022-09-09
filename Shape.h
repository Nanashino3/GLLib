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
	void Execute() const;

protected:
	const GLsizei mVertexNum;
	const GLsizei mIndexNum;

private:
	std::shared_ptr<const Figure> mFigure;
};