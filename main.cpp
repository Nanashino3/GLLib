#include <iostream>
#define GLAD_GL_IMPLEMENTATION

#include "GLLib.h"

int main()
{
	// OpenGLŠÖ˜A‚Ì‰Šú‰»
	if(!GLLibInit()){
		std::cerr << "GLLibInit Error." << std::endl;
		return 1;
	}

	// ”wŒiF‚ğŒˆ’è
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	while(!ProcessMessage()){
		glClear(GL_COLOR_BUFFER_BIT);

		SwapBuffers();
	}

	GLLibEnd();
}