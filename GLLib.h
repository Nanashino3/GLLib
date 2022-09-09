#pragma once

#include <GLFW/glfw3.h>

namespace tkl
{
bool LibraryInit();
bool ProcessMessage();
void SwapBuffers();
void LibraryEnd();

int DrawBox(int, int, int, int, unsigned int, int);
int DrawBox3D(int, int, int, int, unsigned int, int);
}