#pragma once
#include <GL/glew.h>

// 図形クラス
class Figure
{
public:
	struct Vertex
	{
		GLfloat position[3];	// 位置
		GLfloat color[3];		// 色
	};

	Figure(GLint, GLsizei, const Vertex*, GLsizei indexCount = 0, const GLuint* index = 0);
	~Figure();

	void Bind() const;

private:
	Figure(const Figure&);
	Figure& operator=(const Figure&);

private:
	GLuint mVertexArray;	// 頂点配列オブジェクト
	GLuint mVertexBuffer;	// 頂点バッファオブジェクト
	GLuint mIndexBuffer;	// 頂点バッファオブジェクト(インデックス)
};