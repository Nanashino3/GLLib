#pragma once

#include "Vector3.h"

class Quaternion
{
public:
	float mX, mY, mZ;	// �x�N�g��(qv)
	float mW;			// �X�J���[(qs)
	
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

//	// ���K�����ꂽ��]���Ɖ�]�p����N�H�[�^�j�I�����v�Z����
//	Quaternion(const Vector3& axis, float angle)
//	{
//		// qv = ���K�����ꂽ�x�N�g�� * sin(��/2)
//		float scalar = sinf(angle / 2.0f);
//		mX = axis.mX * scalar;
//		mY = axis.mY * scalar;
//		mZ = axis.mZ * scalar;
//		
//		// qs = cos(��/2)
//		mW = cosf(angle / 2.0f);
//	}

	// �����N�H�[�^�j�I��
	void Conjugate()
	{
		mX *= -1.0f;
		mY *= -1.0f;
		mZ *= -1.0f;
	}

	// �P�ʃN�H�[�^�j�I��
	static Quaternion Identity()
	{
		return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	}

	// ��]�p�Ɖ�]������N�H�[�^�j�I�����쐬����
	static Quaternion AngleAxis(const Vector3& axis, float angle)
	{
		Quaternion temp;
		// qv = ���K�����ꂽ�x�N�g�� * sin(��/2)
		float scalar = sinf(angle / 2.0f);
		temp.mX = axis.mX * scalar;
		temp.mY = axis.mY * scalar;
		temp.mZ = axis.mZ * scalar;
		
		// qs = cos(��/2)
		temp.mW = cosf(angle / 2.0f);

		return temp;
	}

	//// �N�H�[�^�j�I���̌���
	//static Quaternion Concatenate(const Quaternion& q, const Quaternion& p)
	//{
	//	Vector3 qv(q.mX, q.mY, q.mZ);
	//	Vector3 pv(p.mX, p.mY, p.mZ);
	//	// �O���X�}����
	//	// (pq)v = ps * qv + qs * pv + cross(pv, qv);
	//	Vector3 newVector = p.mW * qv + q.mW * pv + Vector3::Cross(pv, qv);
	//	// (pq)s = ps * qs - dot(pv, qv);
	//	float newScalar = p.mW * q.mW - Vector3::Dot(pv, qv);

	//	// �N�H�[�^�j�I���Ƃ��ĕԋp
	//	return Quaternion(newVector.mX, newVector.mY, newVector.mZ, newScalar);
	//}

	// �N�H�[�^�j�I���Ńx�N�g������]������
	static Vector3 Transform(const Vector3& v, const Quaternion& q)
	{
		Vector3 qv(q.mX, q.mY, q.mZ);
		Vector3 newVector = v;

		newVector += 2.0f * Vector3::Cross(qv, Vector3::Cross(qv, v) + q.mW * v);
		return newVector;
	}
};