#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

bool GLLibInit();
void GLLibEnd();

bool ProcessMessage();
void SwapBuffers();

int DrawBox(int, int, int, int, unsigned int, int);