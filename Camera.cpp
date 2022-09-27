#include "Camera.h"
#include "Matrix.h"
#include "System.h"

Camera::Camera(int screenW, int screenH)
: mCamPos(Vector3(3.0f, 4.0f, 5.0f))
, mTargetPos(Vector3(0.0f, 0.0f, 0.0f))
, mUpVector(Vector3(0.0f, 1.0f, 0.0f))
, mScreenW(screenW)
, mScreenH(screenH)
, mAngle(60.0f)
, mAspect(static_cast<float>(screenW)/static_cast<float>(screenH))
, mNear(1.0f)
, mFar(5000.0f)
{}

void Camera::Update()
{
	Matrix vpm = Matrix::PerspectiveProjection(mAngle, mAspect, mNear, mFar);
	vpm *= Matrix::LookAt(mCamPos, mTargetPos, mUpVector);

	System::GetInstance()->SetViewProjection(vpm);
}