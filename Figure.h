#pragma once
#include <GL/glew.h>

class Figure
{
public:
	struct Vertex
	{
		GLfloat position[2];	// 位置
	};

	Figure(GLint dimension, GLsizei vertexNum, const Vertex* vertex, GLsizei indexCount = 0, const GLuint* index = 0);
	~Figure();

	void Bind() const;

private:
	Figure(const Figure&);
	Figure& operator=(const Figure&);

private:
	GLuint mVao;	// 頂点配列オブジェクト
	GLuint mVbo;	// 頂点バッファオブジェクト
	GLuint mIbo;	// 頂点バッファオブジェクト(インデックス)
};