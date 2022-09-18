#pragma once

#include <math.h>
class Vector3
{
public:
	Vector3() : mX(0.0f), mY(0.0f), mZ(0.0f){}
	Vector3(float x, float y, float z) : mX(x), mY(y), mZ(z){}

	const float* GetAsFloatPtr() const{ return reinterpret_cast<const float*>(&mX); }

	// 加算
	friend Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.mX + b.mX, a.mY + b.mY, a.mZ + b.mZ);
	}

	// 減算
	friend Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.mX - b.mX, a.mY - b.mY, a.mZ - b.mZ);
	}

	// ベクトル同士の乗算
	friend Vector3 operator*(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.mX * b.mX, a.mY * b.mY, a.mZ * b.mZ);
	}

	// スカラーとベクトルの乗算
	friend Vector3 operator*(const float s, const Vector3& a)
	{
		return Vector3(s * a.mX, s * a.mY, s * a.mZ);
	}

	// ベクトルの正規化
	static Vector3 Normalize(const Vector3& v)
	{
		Vector3 temp;
		float len = sqrtf(v.mX * v.mX + v.mY * v.mY + v.mZ * v.mZ);
		len = (len > 0.0f) ? 1.0f / len : len;
		temp.mX = v.mX * len;
		temp.mY = v.mY * len;
		temp.mZ = v.mZ * len;
		return temp;
	}

	// 内積
	static GLfloat Dot(const Vector3& v1, const Vector3& v2)
	{
		return v1.mX * v2.mX + v1.mY * v2.mY + v1.mZ * v2.mZ;
	}

	// 外積
	static Vector3 Cross(const Vector3& v1, const Vector3& v2)
	{
		Vector3 temp;
		temp.mX = v1.mY * v2.mZ - v1.mZ * v2.mY;
		temp.mY = v1.mZ * v2.mX - v1.mX * v2.mZ;
		temp.mZ = v1.mX * v2.mY - v1.mY * v2.mX;
		return temp;
	}

	static GLfloat Length(const Vector3& v)
	{
		return sqrtf(v.mX * v.mX + v.mY * v.mY + v.mZ * v.mZ);
	}

	float mX, mY, mZ;
};