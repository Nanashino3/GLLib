#pragma once

#include "Matrix.h"

class Quaternion
{
public:
	float mX, mY, mZ;	// ベクトル(qv)
	float mW;			// スカラー(qs)

	Quaternion(float x, float y, float z, float w)
	: mX(x), mY(y), mZ(z), mW(w)
	{}

	// 正規化された回転軸と回転角からクォータニオンを計算する
	Quaternion(const Vector3& axis, float angle)
	{
		// qv = 正規化されたベクトル * sin(θ/2)
		float scalar = sinf(angle / 2.0f);
		mX = axis.mX * scalar;
		mY = axis.mY * scalar;
		mZ = axis.mZ * scalar;
		
		// qs = cos(θ/2)
		mW = cosf(angle / 2.0f);
	}

	// クォータニオンの結合
	static Quaternion Concatenate(const Quaternion& q, const Quaternion& p)
	{
		Vector3 qv(q.mX, q.mY, q.mZ);
		Vector3 pv(p.mX, p.mY, p.mZ);
		// グラスマン積
		// (pq)v = ps * qv + qs * pv + cross(pv, qv);
		Vector3 newVector = p.mW * qv + q.mW * pv + Vector3::Cross(pv, qv);
		// (pq)s = ps * qs - dot(pv, qv);
		float newScalar = p.mW * q.mW - Vector3::Dot(pv, qv);

		// クォータニオンとして返却
		return Quaternion(newVector.mX, newVector.mY, newVector.mZ, newScalar);
	}

	// クォータニオン行列の作成
	static Matrix CreateQuaternion(const Quaternion& q)
	{
		// 単位クォータニオンの場合の式になる
		// | 1-2qy^2-2qz^2 2qxqy-2qwqz   2qxqz+2qwqy   0 |
		// | 2qxqy+2qwqz   1-2qx^2-2qz^2 2qyqz-2qwqx   0 |
		// | 2qxqz-2qwqy   2qyqz+2qwqx   1-2qx^2-2qy^2 0 |
		// | 0             0             0             1 |

		Matrix temp;
		temp.Identity();
		
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

};