#pragma once

#include "Vector3.h"
#include "Quaternion.h"
#include "Camera.h"

namespace tkl
{
class Mesh
{
public:

	Vector3 mPos;
	Vector3 mScale;
	Quaternion mRotate;

	void Render(const Camera* camera);
};

} // namespace tkl