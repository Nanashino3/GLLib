#pragma once

#include <GLFW/glfw3.h>

namespace tkl
{
bool LibraryInit();
bool ProcessMessage();
void SwapBuffers();
void LibraryEnd();

int DrawBox(float, float, float, float, unsigned int, int);
int DrawCube(float, float, float, float, float, unsigned int, int);
int DrawSphere(float, float, float, float, int, int);
}