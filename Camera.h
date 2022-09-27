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
	int mScreenW;	// 画面サイズ(横幅)
	int mScreenH;	// 画面サイズ(高さ)

	float mAngle;	// 画角(角度指定)
	float mAspect;	// アスペクト比(縦横比)
	float mNear;	// 表示範囲(最近距離)
	float mFar;		// 表示範囲(最遠距離)
};