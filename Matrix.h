#pragma once

#include <algorithm>
#include <math.h>

#include "Vector.h"

// 行列クラス
class Matrix
{
public:
	// コンストラクタ
	Matrix(){}
	Matrix(const GLfloat* a)
	{
		// 配列の内容で初期化
		std::copy(a, a + 16, mMatrix);
	}

	const GLfloat& operator[](std::size_t i) const { return mMatrix[i]; }
	GLfloat& operator[](std::size_t i){ return mMatrix[i]; }
	
	// 乗算
	Matrix operator*(const Matrix& m) const
	{
		Matrix temp;
		for(int i = 0; i < 16; ++i){
			const int j = i & 3;	// 0011
			const int k = i & ~3;	// 1100

			temp[i] = mMatrix[0  + j] * m[k + 0] +
					  mMatrix[4  + j] * m[k + 1] +
					  mMatrix[8  + j] * m[k + 2] +
					  mMatrix[12 + j] * m[k + 3];
		}

		return temp;
	}

	// 変換行列の配列を返す
	const GLfloat* Data() const{ return mMatrix; }

	// 単位行列を設定
	void LoadIdentity()
	{
		std::fill(mMatrix, mMatrix + 16, 0.0f);
		mMatrix[0] = mMatrix[5] = mMatrix[10] = mMatrix[15] = 1.0f;
	}

	// 単位行列を作成
	static Matrix Identity()
	{
		Matrix temp;
		temp.LoadIdentity();
		return temp;
	}

	// 平行移動行列を作成
	static Matrix Translate(GLfloat x, GLfloat y, GLfloat z)
	{
		Matrix temp;
		temp.LoadIdentity();
		temp[12] = x;
		temp[13] = y;
		temp[14] = z;
		return temp;
	}

	// 拡大縮小行列作成
	static Matrix Scale(GLfloat x, GLfloat y, GLfloat z)
	{
		Matrix temp;
		temp.LoadIdentity();
		temp[0]  = x;
		temp[5]  = y;
		temp[10] = z;
		return temp;
	}

	// X軸回転の行列作成
	static Matrix RotationX(GLfloat x)
	{
		Matrix temp;
		temp.LoadIdentity();

		float sin = std::sinf(x);
		float cos = std::cosf(x);

		temp[5]  = cos; temp[6]  = -sin;
		temp[9]  = sin; temp[10] = cos;
		return temp;
	}

	// Y軸回転の行列作成
	static Matrix RotationY(GLfloat y)
	{
		Matrix temp;
		temp.LoadIdentity();

		float sin = std::sinf(y);
		float cos = std::cosf(y);

		temp[0] =  cos;	temp[2]  = sin;
		temp[8] = -sin; temp[10] = cos;
		return temp;
	}

	// Z軸回転の行列作成
	static Matrix RotationZ(GLfloat z)
	{
		Matrix temp;
		temp.LoadIdentity();

		float sin = std::sinf(z);
		float cos = std::cosf(z);

		temp[0] = cos; temp[1] = -sin;
		temp[4] = sin; temp[5] =  cos;
		return temp;
	}

	// ビュー行列
	static Matrix LookAt(const Vector3& camPos, const Vector3& targetPos, const Vector3& up)
	{
#if 1
		// カメラ座標作成
		Vector3 zAxis = Vector3::Normalize(camPos - targetPos);
		Vector3 xAxis = Vector3::Normalize(Vector3::Cross(up, zAxis));
		Vector3 yAxis = Vector3::Normalize(Vector3::Cross(zAxis, xAxis));

		Vector3 trans;
		trans.mX = -Vector3::Dot(xAxis, camPos);
		trans.mY = -Vector3::Dot(yAxis, camPos);
		trans.mZ = -Vector3::Dot(zAxis, camPos);

		Matrix temp;
		temp.LoadIdentity();
		temp[0]  = xAxis.mX; temp[1]  = yAxis.mX; temp[2]  = zAxis.mX;
		temp[4]  = xAxis.mY; temp[5]  = yAxis.mY; temp[6]  = zAxis.mZ;
		temp[8]  = xAxis.mZ; temp[9]  = yAxis.mZ; temp[10] = zAxis.mZ;
		temp[12] = trans.mX; temp[13] = trans.mY; temp[14] = trans.mZ;

		return temp;
#else
		// 視点を原点に合わせる
		const Matrix translate = Translate(-camPos.mX, -camPos.mY, -camPos.mZ);

		// 各軸のベクトルを計算する
		Vector3 zAxis = camPos - targetPos;				// t軸
		Vector3 xAxis = Vector3::Cross(up, zAxis);		// r軸
		Vector3 yAxis = Vector3::Cross(zAxis, xAxis);	// s軸

		// 長さのチェック
		const GLfloat length = Vector3::Length(yAxis);
		if(length == 0.0f) return translate;

		// 回転行列を作成する
		Matrix rotation;
		rotation.LoadIdentity();
		
		// 各軸正規化して回転行列に格納
		Vector3 xAxisNormalize = Vector3::Normalize(xAxis);
		rotation[0]  = xAxisNormalize.mX;
		rotation[4]  = xAxisNormalize.mY;
		rotation[8]  = xAxisNormalize.mZ;

		Vector3 yAxisNormalize = Vector3::Normalize(yAxis);
		rotation[1]  = yAxisNormalize.mX;
		rotation[5]  = yAxisNormalize.mY;
		rotation[9]  = yAxisNormalize.mZ;

		Vector3 zAxisNormalize = Vector3::Normalize(zAxis);
		rotation[2]  = zAxisNormalize.mX;
		rotation[6]  = zAxisNormalize.mY;
		rotation[10] = zAxisNormalize.mZ;

		// 視点の平行移動と視線の回転を一つにする
		return rotation * translate;
#endif
	}


	// 単純なビュー射影行列
	static Matrix SimpleViewProjection(GLfloat width, GLfloat height)
	{
		Matrix temp;
		temp.LoadIdentity();
		temp[0]  = 2.0f / width;
		temp[5]  = 2.0f / height;
		temp[14] = 1.0f;

		return temp;
	}
	 
	// 正射影行列
	static Matrix OrthogonalProjection(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far)
	{
		Matrix temp;
		temp.LoadIdentity();

		const GLfloat ral = right + left;	// right add left
		const GLfloat rsl = right - left;	// right subtraction left
		const GLfloat tab = top + bottom;	// top add bottom
		const GLfloat tsb = top - bottom;	// top subtraction bottom
		const GLfloat fan = far + near;		// far add near
		const GLfloat fsn = far - near;		// far subtraction near

		temp[0]  = 2.0f / rsl;
		temp[5]  = 2.0f / tsb;
		temp[10] = -2.0f / fsn;
		temp[12] = -ral / rsl;
		temp[13] = -tab / tsb;
		temp[14] = -fan / fsn;

		return temp;
	}

private:
	GLfloat mMatrix[16];
};