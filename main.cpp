
#include <iostream>

#include "GLLib.h"
#include "Input.h"

int main()
{

	// OpenGL�֘A�̏�����
	if(!tkl::LibraryInit()){
		std::cerr << "LibraryInit Error." << std::endl;
		return 1;
	}

	// �w�i�F������
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	float x = 0.0f, y = 0.0f, z = 0.0f;
	while(!tkl::ProcessMessage()){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if(tkl::Input::IsKeyDown(eKeys::KB_A)){
			//std::cout << "A��������Ă��܂�" << std::endl;
			x -= 0.1f;
		}
		if(tkl::Input::IsKeyDown(eKeys::KB_D)){
			//std::cout << "A��������Ă��܂�" << std::endl;
			x += 0.1f;
		}
		if(tkl::Input::IsKeyDown(eKeys::KB_S)){
			z -= 0.1f;
		}
		if(tkl::Input::IsKeyDown(eKeys::KB_W)){
			z += 0.1f;
		}
		
//		tkl::DrawBox(x, y, 50, 50, -1, true);
		tkl::DrawCube(x, y, z, 1.0f, 1.0f, 1.0f, -1, true);
//		tkl::DrawSphere(x, y, 0.0f, 1.0f, 24, 16);

		tkl::SwapBuffers();
	}

	tkl::LibraryEnd();

	return 0;
}