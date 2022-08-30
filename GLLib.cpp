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

int DrawBox(/*int fx, int fy, int ex, int ey, unsigned int color, int fillFlag*/)
{
	return System::GetInstance()->DrawBox();
}

int DrawTriangle(/*int, int, int, int, unsigned int, int*/)
{
	return 0;
}

}