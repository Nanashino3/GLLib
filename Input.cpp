#include "Input.h"

namespace tkl
{
bool Input::sKeyDownState[GLFW_KEY_LAST] = { false };

Input::Input()
{}

Input::~Input()
{}

bool Input::IsKeyDown(int key)
{
	return sKeyDownState[key];
}

void Input::Update(GLFWwindow* const window)
{
	ProcessGetKeyInput(window);
}

void Input::ProcessGetKeyInput(GLFWwindow* const window)
{
	// ï˚å¸ÉLÅ[
	for (int i = GLFW_KEY_RIGHT; i <= GLFW_KEY_UP; ++i)
		sKeyDownState[i] = glfwGetKey(window, i);

	sKeyDownState[GLFW_KEY_A] = glfwGetKey(window, GLFW_KEY_A);
	sKeyDownState[GLFW_KEY_S] = glfwGetKey(window, GLFW_KEY_S);
	sKeyDownState[GLFW_KEY_D] = glfwGetKey(window, GLFW_KEY_D);
	sKeyDownState[GLFW_KEY_W] = glfwGetKey(window, GLFW_KEY_W);

	sKeyDownState[GLFW_KEY_Z] = glfwGetKey(window, GLFW_KEY_Z);
	sKeyDownState[GLFW_KEY_X] = glfwGetKey(window, GLFW_KEY_X);
	sKeyDownState[GLFW_KEY_C] = glfwGetKey(window, GLFW_KEY_C);

	sKeyDownState[GLFW_KEY_SPACE] = glfwGetKey(window, GLFW_KEY_SPACE);
	sKeyDownState[GLFW_KEY_ENTER] = glfwGetKey(window, GLFW_KEY_ENTER);
}

}