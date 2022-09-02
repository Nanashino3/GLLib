
#include <iostream>

#include "GLLib.h"
#include "Input.h"

int main()
{
	// OpenGL関連の初期化
	if(!tkl::LibraryInit()){
		std::cerr << "LibraryInit Error." << std::endl;
		return 1;
	}

	// 背景色を決定
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	int x = 0, y = 0;
	while(!tkl::ProcessMessage()){
		glClear(GL_COLOR_BUFFER_BIT);
		
		if(tkl::Input::IsKeyDownTrigger(eKeys::KB_A)){
			std::cout << "Aが押されています" << std::endl;
		}
		tkl::DrawBox(x, y, 50, 50, -1, true);

		tkl::SwapBuffers();
	}

	tkl::LibraryEnd();

	return 0;
}