
#include "Figure.h"

Figure::Figure(GLint dimension, GLsizei vertexNum, const Vertex* vertex, GLsizei indexCount, const GLuint* index)
{
	// 頂点配列オブジェクト
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	// 頂点バッファオブジェクト
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexNum * sizeof(Vertex), vertex, GL_STATIC_DRAW);

	// インデックスの頂点バッファオブジェクト
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), index, GL_STATIC_DRAW);

	// 結合されている頂点バッファオブジェクトをin変数から参照できるようにする
	glVertexAttribPointer(0, dimension, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->position);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, dimension, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->color);
	glEnableVertexAttribArray(1);
}

Figure::~Figure()
{
	// 頂点バッファオブジェクトを削除する
	glDeleteBuffers(1, &mVertexBuffer);
	// インデックスの頂点バッファオブジェクトを削除する
	glDeleteBuffers(1, &mIndexBuffer);
	// 頂点配列オブジェクトを削除する
	glDeleteVertexArrays(1, &mVertexArray);
}

// 頂点配列オブジェクトの結合
void Figure::Bind() const
{
	glBindVertexArray(mVertexArray);
}