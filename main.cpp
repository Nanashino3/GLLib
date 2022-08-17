#include <iostream>
#define GLAD_GL_IMPLEMENTATION

#include "GLLib.h"

int main()
{
	// OpenGL関連の初期化
	if(!GLLibInit()){
		std::cerr << "GLLibInit Error." << std::endl;
		return 1;
	}

	// 背景色を決定
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	while(!ProcessMessage()){
		glClear(GL_COLOR_BUFFER_BIT);

		SwapBuffers();
	}

	GLLibEnd();
}