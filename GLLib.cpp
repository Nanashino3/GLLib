#include "GLLib.h"
#include "System.h"

namespace tkl
{
bool LibraryInit()
{
	System::GetInstance()->Initialize();
	return true;
}

bool ProcessMessage()
{
	return System::GetInstance()->ProcessMessage();
}

void SwapBuffers()
{
	System::GetInstance()->DoubleBuffering();
}

void LibraryEnd()
{
	System::GetInstance()->Finalize();
}

int DrawBox(float posX, float posY, float width, float height, unsigned int color, int fillFlag)
{
	return System::GetInstance()->DrawBox(posX, posY, width, height, color, fillFlag);
}

int DrawCube(float posX, float posY, float posZ, float width, float height, float depth, unsigned int color, int fillFlag)
{
	return System::GetInstance()->DrawCube(posX, posY, posZ, width, height, depth, color, fillFlag);
}

int DrawSphere(float posX, float posY, float posZ, float radius, int divWidth, int divHeight)
{
	return System::GetInstance()->DrawSphere(posX, posY, posZ, radius, divWidth, divHeight);
}

int DrawPlane(float posX, float posY, float posZ, float width, float height, float depth, unsigned int color, int fillFlag)
{
	return System::GetInstance()->DrawPlane(posX, posY, posZ, width, height, depth, color, fillFlag);
}

void DirectionalLight()
{
	System::GetInstance()->DirectionalLight();
}

void DrawGridGround(float size, int rowNum, unsigned int color)
{
	System::GetInstance()->DrawGridGround(size, rowNum, color);
}

int LoadGraph(const char* name)
{
	return System::GetInstance()->LoadGraph(name);
}

void DrawGraph(float posX, float posY)
{
	System::GetInstance()->DrawGraph(posX, posY);
}

void DrawGraphPlane(float posX, float posY, float posZ)
{
	System::GetInstance()->DrawGraphPlane(posX, posY, posZ);
}

} // namespace tkl