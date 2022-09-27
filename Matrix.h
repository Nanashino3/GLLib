#pragma once

#include <algorithm>
#include "Util.h"
#include "Quaternion.h"

class Vector3;
class Quaternion;

// 行列クラス
class Matrix
{
public:
	// コンストラクタ
	Matrix(){}
	Matrix(const float* a)
	{
		// 配列の内容で初期化
		std::copy(a, a + 16, mMatrix);
	}

	const float& operator[](std::size_t i) const { return mMatrix[i]; }
	float& operator[](std::size_t i){ return mMatrix[i]; }
	
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
	Matrix& operator*=(const Matrix& m)
	{
		*this = *this * m;
		return *this;
	}

	// 変換行列の配列を返す
	const float* Data() const{ return mMatrix; }

	// 単位行列を作成
	static Matrix Identity()
	{
		Matrix temp;
		temp.LoadIdentity();
		return temp;
	}

	// 平行移動行列を作成
	static Matrix Translate(float x, float y, float z)
	{
		Matrix temp;
		temp.LoadIdentity();
		temp[12] = x;
		temp[13] = y;
		temp[14] = z;
		return temp;
	}

	// 拡大縮小行列作成
	static Matrix Scale(float x, float y, float z)
	{
		Matrix temp;
		temp.LoadIdentity();
		temp[0]  = x;
		temp[5]  = y;
		temp[10] = z;
		return temp;
	}

	// X軸回転の行列作成
	static Matrix RotationX(float x)
	{
		Matrix temp;
		temp.LoadIdentity();

		float sin = sinf(x);
		float cos = cosf(x);

		temp[5]  = cos; temp[6]  = -sin;
		temp[9]  = sin; temp[10] = cos;
		return temp;
	}

	// Y軸回転の行列作成
	static Matrix RotationY(float y)
	{
		Matrix temp;
		temp.LoadIdentity();

		float sin = sinf(y);
		float cos = cosf(y);

		temp[0] =  cos;	temp[2]  = sin;
		temp[8] = -sin; temp[10] = cos;
		return temp;
	}

	// Z軸回転の行列作成
	static Matrix RotationZ(float z)
	{
		Matrix temp;
		temp.LoadIdentity();

		float sin = sinf(z);
		float cos = cosf(z);

		temp[0] = cos; temp[1] = -sin;
		temp[4] = sin; temp[5] =  cos;
		return temp;
	}

	// 任意軸回転(方向余弦)
	static Matrix Rotate(float rotate, const Vector3& vec)
	{
		Matrix temp;
		temp.LoadIdentity();

		float length = Vector3::Length(vec);
		float dx = vec.mX / length, dy = vec.mY / length, dz = vec.mZ / length;
		float cos = cosf(rotate), sin = sinf(rotate);

		temp[0]  = dx * dx + (1.0f - dx * dx) * cos;
		temp[1]  = dx * dy * (1.0f - cos) - dz * sin;
		temp[2]  = dx * dz * (1.0f - cos) + dy * sin;
		
		temp[4]  = dy * dx * (1.0f - cos) + dz * sin;
		temp[5]  = dy * dy + (1.0f - dy * dy) * cos;
		temp[6]  = dy * dz * (1.0f - cos) - dx * sin;

		temp[8]  = dz * dx * (1.0f - cos) - dy * sin;
		temp[9]  = dz * dy * (1.0f - cos) + dx * sin;
		temp[10] = dz * dz + (1.0f - dz * dz) * cos;

		return temp;
	}

	// ビュー行列
	static Matrix LookAt(const Vector3& camPos, const Vector3& targetPos, const Vector3& up)
	{
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
		temp[4]  = xAxis.mY; temp[5]  = yAxis.mY; temp[6]  = zAxis.mY;
		temp[8]  = xAxis.mZ; temp[9]  = yAxis.mZ; temp[10] = zAxis.mZ;
		temp[12] = trans.mX; temp[13] = trans.mY; temp[14] = trans.mZ;
		return temp;
	}


	// 単純なビュー射影行列
	static Matrix SimpleViewProjection(float width, float height)
	{
		Matrix temp;
		temp.LoadIdentity();
		temp[0]  = 2.0f / width;
		temp[5]  = 2.0f / height;
		temp[14] = 1.0f;

		return temp;
	}
	 
	// 正射影行列
	static Matrix OrthogonalProjection(float left, float right, float bottom, float top, float near, float far)
	{
		Matrix temp;
		temp.LoadIdentity();

		float ral = right + left;	// right add left
		float rsl = right - left;	// right subtraction left
		float tab = top + bottom;	// top add bottom
		float tsb = top - bottom;	// top subtraction bottom
		float fan = far + near;		// far add near
		float fsn = far - near;		// far subtraction near

		temp[0]  = 2.0f / rsl;
		temp[5]  = 2.0f / tsb;
		temp[10] = -2.0f / fsn;
		temp[12] = -ral / rsl;
		temp[13] = -tab / tsb;
		temp[14] = -fan / fsn;

		return temp;
	}

	// 透視射影行列
	static Matrix PerspectiveProjection(float angle, float aspect, float near, float far)
	{
		Matrix temp;
		temp.LoadIdentity();
		float fovy = ToRadian(angle);

		float fsn = far - near;
		if(fsn != 0.0f){

			temp[5]	 = 1.0f / tanf(fovy * 0.5f);
			temp[0]  = temp[5] / aspect;
			temp[10] = -(far + near) / fsn;
			temp[11] = -1.0f;
			temp[14] = -2.0f * far * near / fsn;
			temp[15] = 0.0f;
		}
		return temp;
	}

	// クォータニオン行列の作成
	static Matrix CreateQuaternion(const Quaternion& q)
	{
		Matrix temp;
		temp.LoadIdentity();

		temp[0]  = 1.0f - 2.0f * q.mY * q.mY - 2.0f * q.mZ * q.mZ;
		temp[1]  = 2.0f * q.mX * q.mY + 2.0f * q.mW * q.mZ;
		temp[2]  = 2.0f * q.mX * q.mZ - 2.0f * q.mW * q.mY;

		temp[4]  = 2.0f * q.mX * q.mY - 2.0f * q.mW * q.mZ;
		temp[5]  = 1.0f - 2.0f * q.mX * q.mX - 2.0f * q.mZ * q.mZ;
		temp[6]  = 2.0f * q.mY * q.mZ + 2.0f * q.mW * q.mX;

		temp[8]  = 2.0f * q.mX * q.mZ + 2.0f * q.mW * q.mY;
		temp[9]  = 2.0f * q.mY * q.mZ - 2.0f * q.mW * q.mX;
		temp[10] = 1.0f - 2.0f * q.mX * q.mX - 2.0f * q.mY * q.mY;
		
		return temp;
	}

private:
	// 単位行列を設定
	void LoadIdentity()
	{
		std::fill(mMatrix, mMatrix + 16, 0.0f);
		mMatrix[0] = mMatrix[5] = mMatrix[10] = mMatrix[15] = 1.0f;
	}

private:
	float mMatrix[16];
};