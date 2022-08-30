
#include <iostream>

#include "GLLib.h"

int main()
{
	// OpenGL関連の初期化
	if(!tkl::LibraryInit()){
		std::cerr << "LibraryInit Error." << std::endl;
		return 1;
	}

	// 背景色を決定
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	while(!tkl::ProcessMessage()){
		glClear(GL_COLOR_BUFFER_BIT);

		tkl::DrawBox();

		tkl::SwapBuffers();
	}

	tkl::LibraryEnd();

	return 0;
}