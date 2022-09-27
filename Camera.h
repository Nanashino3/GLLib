#pragma once

#include "Vector3.h"
class Camera
{
public:
	Camera(int screenW = 640, int screenH = 480);

	void Update();

	Vector3 mCamPos;
	Vector3 mTargetPos;
	Vector3 mUpVector;

private:
	int mScreenW;	// ��ʃT�C�Y(����)
	int mScreenH;	// ��ʃT�C�Y(����)

	float mAngle;	// ��p(�p�x�w��)
	float mAspect;	// �A�X�y�N�g��(�c����)
	float mNear;	// �\���͈�(�ŋߋ���)
	float mFar;		// �\���͈�(�ŉ�����)
};