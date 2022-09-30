
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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	Camera* camera = new Camera();

	tkl::LoadGraph("Assets/Ship.png");

	float x = 0.0f, y = 0.0f, z = 0.0f;
	while(!tkl::ProcessMessage()){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if(tkl::Input::IsKeyDown(eKeys::KB_A)){
			//std::cout << "A‚ª‰Ÿ‚³‚ê‚Ä‚¢‚Ü‚·" << std::endl;
			x -= 0.1f;
		}
		if(tkl::Input::IsKeyDown(eKeys::KB_D)){
			//std::cout << "A‚ª‰Ÿ‚³‚ê‚Ä‚¢‚Ü‚·" << std::endl;
			x += 0.1f;
		}
		if(tkl::Input::IsKeyDown(eKeys::KB_S)){
			y += 0.1f;
		}
		if(tkl::Input::IsKeyDown(eKeys::KB_W)){
			y -= 0.1f;
		}
		
//		camera->Update();

//		tkl::DrawBox(x, y, 50.0f, 50.0f, -1, true);
//		tkl::DrawGraph(x, y);

//		tkl::DrawCube(x, y, z, 1.0f, 1.0f, 1.0f, -1, true);
//		tkl::DrawSphere(x, y,  0.0f, 1.0f, 16, 8);
//		tkl::DrawPlane(x, y, z, 1.0f, 1.0f, 1.0f, -1, true);
//		tkl::DirectionalLight();

//		tkl::DrawGridGround(50.0f, 10.0f);

		tkl::SwapBuffers();
	}

	tkl::LibraryEnd();

	return 0;
}