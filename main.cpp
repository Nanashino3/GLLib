
#include <iostream>

#include "GLLib.h"

#include "Camera.h"
#include "Input.h"

int main()
{

	// OpenGLŠÖ˜A‚Ì‰Šú‰»
	if(!tkl::LibraryInit()){
		std::cerr << "LibraryInit Error." << std::endl;
		return 1;
	}

	// ”wŒiF‚ğŒˆ’è
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Camera* camera = new Camera();
//	Mesh* cube = CreateCube();

	float x = 0.0f, y = 0.0f, z = 0.0f;
	while(!tkl::ProcessMessage()){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
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
		
		camera->Update();

//		tkl::DrawCube(x, y, z, 1.0f, 1.0f, 1.0f, -1, true);
//		tkl::DrawSphere(x, y, z, 1.0f, 16, 8);
		tkl::DrawPlane(x, y, z, 1.0f, 1.0f, 1.0f, -1, true);
		tkl::DirectionalLight();

		tkl::SwapBuffers();
	}

	tkl::LibraryEnd();

	return 0;
}