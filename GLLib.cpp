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

int DrawBox3D(float posX, float posY, float width, float height, unsigned int color, int fillFlag)
{
	return System::GetInstance()->DrawBox3D(posX, posY, width, height, color, fillFlag);
}

}