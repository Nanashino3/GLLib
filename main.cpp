
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
		
		if(tkl::Input::IsKeyDown(GLFW_KEY_W)){
			y -= 1;
		}else if(tkl::Input::IsKeyDown(GLFW_KEY_S)){
			y += 1;
		}else if(tkl::Input::IsKeyDown(GLFW_KEY_A)){
			x -= 1;
		}else if(tkl::Input::IsKeyDown(GLFW_KEY_D)){
			x += 1;
		}
		tkl::DrawBox(x, y, 50, 50, -1, true);

		tkl::SwapBuffers();
	}

	tkl::LibraryEnd();

	return 0;
}