#pragma once

#include <algorithm>

// �s��N���X
class Matrix
{
public:
	// �R���X�g���N�^
	Matrix(){}
	Matrix(const GLfloat* a)
	{
		// �z��̓��e�ŏ�����
		std::copy(a, a + 16, mMatrix);
	}

	const GLfloat& operator[](std::size_t i) const { return mMatrix[i]; }
	GLfloat& operator[](std::size_t i){ return mMatrix[i]; }
	
	// ��Z
	Matrix operator*(const Matrix& m) const
	{
		Matrix temp;
		temp.LoadIdentity();

		for(int i = 0; i < 16; ++i){
			const int j = i & 3;	// 0011
			const int k = i & ~3;	// 1100

			temp[i] = temp[0 + j] * temp[k + 0] +
					  temp[1 + j] * temp[k + 1] +
					  temp[2 + j] * temp[k + 2] +
					  temp[3 + j] * temp[k + 3];
		}

		return temp;
	}

	// �ϊ��s��̔z���Ԃ�
	const GLfloat* Data() const{ return mMatrix; }

	// �P�ʍs���ݒ�
	void LoadIdentity()
	{
		std::fill(mMatrix, mMatrix + 16, 0.0f);
		mMatrix[0] = mMatrix[5] = mMatrix[10] = mMatrix[15] = 1.0f;
	}

	// �P�ʍs����쐬
	static Matrix Identity()
	{
		Matrix temp;
		temp.LoadIdentity();
		return temp;
	}

	// ���s�ړ��s����쐬
	static Matrix Translate(GLfloat x, GLfloat y, GLfloat z)
	{
		Matrix temp;
		temp.LoadIdentity();
		temp[12] = x;
		temp[13] = y;
		temp[14] = z;
		return temp;
	}

	// �g��k���s��쐬
	static Matrix Scale(GLfloat x, GLfloat y, GLfloat z)
	{
		Matrix temp;
		temp.LoadIdentity();
		temp[0]  = x;
		temp[5]  = y;
		temp[10] = z;
		return temp;
	}

	// ���ˉe�s��
	static Matrix OrthogonalProjection(GLfloat width, GLfloat height)
	{
		Matrix temp;
		temp.LoadIdentity();
		temp[0]  = 2.0f / width;
		temp[5]  = 2.0f / height;
		temp[14] = 1.0f;

		return temp;
	}

private:
	GLfloat mMatrix[16];
};