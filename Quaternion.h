#pragma once

#include "Matrix.h"

class Quaternion
{
public:
	float mX, mY, mZ;	// �x�N�g��(qv)
	float mW;			// �X�J���[(qs)

	Quaternion(float x, float y, float z, float w)
	: mX(x), mY(y), mZ(z), mW(w)
	{}

	// ���K�����ꂽ��]���Ɖ�]�p����N�H�[�^�j�I�����v�Z����
	Quaternion(const Vector3& axis, float angle)
	{
		// qv = ���K�����ꂽ�x�N�g�� * sin(��/2)
		float scalar = sinf(angle / 2.0f);
		mX = axis.mX * scalar;
		mY = axis.mY * scalar;
		mZ = axis.mZ * scalar;
		
		// qs = cos(��/2)
		mW = cosf(angle / 2.0f);
	}

	// �N�H�[�^�j�I���̌���
	static Quaternion Concatenate(const Quaternion& q, const Quaternion& p)
	{
		Vector3 qv(q.mX, q.mY, q.mZ);
		Vector3 pv(p.mX, p.mY, p.mZ);
		// �O���X�}����
		// (pq)v = ps * qv + qs * pv + cross(pv, qv);
		Vector3 newVector = p.mW * qv + q.mW * pv + Vector3::Cross(pv, qv);
		// (pq)s = ps * qs - dot(pv, qv);
		float newScalar = p.mW * q.mW - Vector3::Dot(pv, qv);

		// �N�H�[�^�j�I���Ƃ��ĕԋp
		return Quaternion(newVector.mX, newVector.mY, newVector.mZ, newScalar);
	}

	// �N�H�[�^�j�I���s��̍쐬
	static Matrix CreateQuaternion(const Quaternion& q)
	{
		// �P�ʃN�H�[�^�j�I���̏ꍇ�̎��ɂȂ�
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