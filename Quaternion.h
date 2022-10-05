#pragma once

#include "Vector3.h"

class Quaternion
{
public:
	float mX, mY, mZ;	// ベクトル(qv)
	float mW;			// スカラー(qs)
	
	Quaternion()
	: mX(0.0f), mY(0.0f), mZ(0.0f), mW(1.0f)
	{}

	Quaternion(float x, float y, float z, float w)
	: mX(x), mY(y), mZ(z), mW(w)
	{}

	Quaternion operator*(const Quaternion& a) const
	{
		Quaternion temp;
		temp.mX = mW * a.mX + mX * a.mW + mZ * a.mY - mY * a.mZ;
		temp.mY = mW * a.mY + mY * a.mW + mX * a.mZ - mZ * a.mX;
		temp.mZ = mW * a.mZ + mZ * a.mW + mY * a.mX - mX * a.mY;
		temp.mW = mW * a.mW - mX * a.mX - mY * a.mY - mZ * a.mZ;
		return temp;
	}
	Quaternion& operator*=(const Quaternion &q)
	{
		*this = *this * q;
		return *this;
	}

	// 共役クォータニオン
	void Conjugate()
	{
		mX *= -1.0f;
		mY *= -1.0f;
		mZ *= -1.0f;
	}

	// 単位クォータニオン
	static Quaternion Identity()
	{
		return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	}

	// 回転角と回転軸からクォータニオンを作成する
	static Quaternion AngleAxis(const Vector3& axis, float angle)
	{
		Quaternion temp;
		// qv = 正規化されたベクトル * sin(θ/2)
		float scalar = sinf(angle / 2.0f);
		temp.mX = axis.mX * scalar;
		temp.mY = axis.mY * scalar;
		temp.mZ = axis.mZ * scalar;
		
		// qs = cos(θ/2)
		temp.mW = cosf(angle / 2.0f);

		return temp;
	}

	// クォータニオンでベクトルを回転させる
	static Vector3 Transform(const Vector3& v, const Quaternion& q)
	{
#if 0
		Vector3 qv(q.mX, q.mY, q.mZ);
		Vector3 newVector = v;

		newVector += 2.0f * Vector3::Cross(qv, Vector3::Cross(qv, v) + q.mW * v);
		return newVector;
#else
		float w = -q.mX * v.mX - q.mY * v.mY - q.mZ * v.mZ;
		float x =  q.mY * v.mZ - q.mZ * v.mY + q.mW * v.mX;
		float y =  q.mZ * v.mX - q.mX * v.mZ + q.mW * v.mY;
		float z =  q.mX * v.mY - q.mY * v.mX + q.mW * v.mZ;

		float vx = y * -q.mZ + z * q.mY - w * q.mX + x * q.mW;
		float vy = z * -q.mX + x * q.mZ - w * q.mY + y * q.mW;
		float vz = x * -q.mY + y * q.mX - w * q.mZ + z * q.mW;

		return Vector3(vx, vy, vz);
#endif
	}
};