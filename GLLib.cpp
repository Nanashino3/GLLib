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

int DrawBox(int posX, int posY, int width, int height, unsigned int color, int fillFlag)
{
	return System::GetInstance()->DrawBox(posX, posY, width, height, color, fillFlag);
}


int DrawBox3D(int posX, int posY, int width, int height, unsigned int color, int fillFlag)
{
	return System::GetInstance()->DrawBox3D(posX, posY, width, height, color, fillFlag);
}

}