#include "Input.h"

#include <iostream>

namespace tkl
{
bool Input::sKeyDownStatus[static_cast<int>(Input::eKeys::KB_MAX)] = { false };
bool Input::sPrevKeyDownStatus[static_cast<int>(Input::eKeys::KB_MAX)] = { false };
bool Input::sKeyDownTrgStatus[static_cast<int>(Input::eKeys::KB_MAX)] = { false };
unsigned short Input::sKeys[static_cast<int>(Input::eKeys::KB_MAX)] = {
		GLFW_KEY_ENTER,			// エンター
		GLFW_KEY_LEFT_SHIFT,	// 左シフト
		GLFW_KEY_RIGHT_SHIFT,	// 右シフト
		GLFW_KEY_SPACE,			// スペース
		GLFW_KEY_LEFT,			// 矢印(左)
		GLFW_KEY_UP,			// 矢印(上)
		GLFW_KEY_RIGHT,			// 矢印(右)
		GLFW_KEY_DOWN,			// 矢印(下)

		// アルファベット
		GLFW_KEY_A,
		GLFW_KEY_B,
		GLFW_KEY_C,
		GLFW_KEY_D,
		GLFW_KEY_E,
		GLFW_KEY_F,
		GLFW_KEY_G,
		GLFW_KEY_H,
		GLFW_KEY_I,
		GLFW_KEY_J,
		GLFW_KEY_K,
		GLFW_KEY_L,
		GLFW_KEY_M,
		GLFW_KEY_N,
		GLFW_KEY_O,
		GLFW_KEY_P,
		GLFW_KEY_Q,
		GLFW_KEY_R,
		GLFW_KEY_S,
		GLFW_KEY_T,
		GLFW_KEY_U,
		GLFW_KEY_V,
		GLFW_KEY_W,
		GLFW_KEY_X,
		GLFW_KEY_Y,
		GLFW_KEY_Z,

		// 数字
		GLFW_KEY_0,
		GLFW_KEY_1,
		GLFW_KEY_2,
		GLFW_KEY_3,
		GLFW_KEY_4,
		GLFW_KEY_5,
		GLFW_KEY_6,
		GLFW_KEY_7,
		GLFW_KEY_8,
		GLFW_KEY_9
};

void Input::Update(GLFWwindow* const window)
{
	InputKeyboard(window);
}

// キー入力
void Input::InputKeyboard(GLFWwindow* const window)
{
	for(int i = 0; i < static_cast<int>(eKeys::KB_MAX); ++i){
		sKeyDownStatus[i] = glfwGetKey(window, sKeys[i]);

		sKeyDownTrgStatus[i] = false;
		if(sPrevKeyDownStatus[i] != sKeyDownStatus[i]){
			if(sKeyDownStatus[i] != GLFW_RELEASE) sKeyDownTrgStatus[i] = true;
		}

		sPrevKeyDownStatus[i] = sKeyDownStatus[i];
	}
}

} // namespace tkl