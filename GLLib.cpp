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

int DrawBox(int fx, int fy, int ex, int ey, unsigned int color, int fillFlag)
{
	int x = fx + 1, y = fy + 1;
	int width = ex + 1, height = ey + 1;
	return System::GetInstance()->DrawBox(x, y, width, height, color, fillFlag);
}

int DrawTriangle(/*int, int, int, int, unsigned int, int*/)
{
	return 0;
}

}