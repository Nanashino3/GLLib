#pragma once
#include <GLFW/glfw3.h>

namespace tkl
{
class Input
{
public:
	~Input();

	static bool IsKeyDown(int);
	static void Update(GLFWwindow* const);

private:
	Input();

	static void ProcessGetKeyInput(GLFWwindow* const);

private:
	static bool sKeyDownState[GLFW_KEY_LAST];
};

} // namespace tkl