#pragma once

#include <math.h>
class Vector3
{
public:
	Vector3() : mX(0.0f), mY(0.0f), mZ(0.0f){}
	Vector3(float x, float y, float z) : mX(x), mY(y), mZ(z){}

	// â¡éZ
	Vector3 operator+(const Vector3& v) const
	{
		Vector3 temp;
		temp.mX = mX + v.mX;
		temp.mY = mY + v.mY;
		temp.mZ = mZ + v.mZ;
		return temp;
	}

	// å∏éZ
	Vector3 operator-(const Vector3& v) const
	{
		Vector3 temp;
		temp.mX = mX - v.mX;
		temp.mY = mY - v.mY;
		temp.mZ = mZ - v.mZ;
		return temp;
	}

	// ÉxÉNÉgÉãÇÃê≥ãKâª
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

	// ì‡êœ
	static GLfloat Dot(const Vector3& v1, const Vector3& v2)
	{
		return v1.mX * v2.mX + v1.mY * v2.mY + v1.mZ * v2.mZ;
	}

	// äOêœ
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