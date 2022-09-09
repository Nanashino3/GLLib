
#include <iostream>

#include "GLLib.h"
#include "Input.h"

int main()
{
	// OpenGLŠÖ˜A‚Ì‰Šú‰»
	if(!tkl::LibraryInit()){
		std::cerr << "LibraryInit Error." << std::endl;
		return 1;
	}

	// ”wŒiF‚ğŒˆ’è
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	int x = 0, y = 0;
	while(!tkl::ProcessMessage()){
		glClear(GL_COLOR_BUFFER_BIT);
		
		if(tkl::Input::IsKeyDown(eKeys::KB_A)){
			//std::cout << "A‚ª‰Ÿ‚³‚ê‚Ä‚¢‚Ü‚·" << std::endl;
			x -= 1.0f;
		}
		if(tkl::Input::IsKeyDown(eKeys::KB_D)){
			//std::cout << "A‚ª‰Ÿ‚³‚ê‚Ä‚¢‚Ü‚·" << std::endl;
			x += 1.0f;
		}
		if(tkl::Input::IsKeyDown(eKeys::KB_S)){
			y += 1.0f;
		}
		if(tkl::Input::IsKeyDown(eKeys::KB_W)){
			y -= 1.0f;
		}
		//tkl::DrawBox(x, y, 50, 50, -1, true);
		tkl::DrawBox3D(x, y, 50, 50, -1, true);

		tkl::SwapBuffers();
	}

	tkl::LibraryEnd();

	return 0;
}