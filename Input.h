#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>

namespace tkl
{
class Input
{
public:

	// キーボード対応一覧
	enum class eKeys
	{
		KB_ENTER,	// エンター
		KB_LSHIFT,	// 左シフト
		KB_RSHIFT,	// 右シフト
		KB_SPACE,	// スペース
		KB_LEFT,	// 矢印(左)
		KB_UP,		// 矢印(上)
		KB_RIGHT,	// 矢印(右)
		KB_DOWN,	// 矢印(下)

		// アルファベット
		KB_A,
		KB_B,
		KB_C,
		KB_D,
		KB_E,
		KB_F,
		KB_G,
		KB_H,
		KB_I,
		KB_J,
		KB_K,
		KB_L,
		KB_M,
		KB_N,
		KB_O,
		KB_P,
		KB_Q,
		KB_R,
		KB_S,
		KB_T,
		KB_U,
		KB_V,
		KB_W,
		KB_X,
		KB_Y,
		KB_Z,

		// 数字
		KB_0,
		KB_1,
		KB_2,
		KB_3,
		KB_4,
		KB_5,
		KB_6,
		KB_7,
		KB_8,
		KB_9,

		KB_MAX
	};

	static void Update(GLFWwindow* const);

	// 押しっぱなし検知(複数キー未対応)
	template<typename eKeys>
	static bool IsKeyDown(eKeys keys){
		return sKeyDownStatus[static_cast<int>(keys)];
	}

	// 1フレーム押し検知(複数キー未対応)
	template<typename eKeys>
	static bool IsKeyDownTrigger(eKeys keys){
		return sKeyDownTrgStatus[static_cast<int>(keys)];
	}

private:
	Input(){}

	static void InputKeyboard(GLFWwindow* const);

private:
	static bool sKeyDownStatus[static_cast<int>(Input::eKeys::KB_MAX)];		// キー押下状態
	static bool sPrevKeyDownStatus[static_cast<int>(Input::eKeys::KB_MAX)];	// 前回のキー押下状態
	static bool sKeyDownTrgStatus[static_cast<int>(Input::eKeys::KB_MAX)];	// キー押下トリガー状態
	static unsigned short sKeys[static_cast<int>(Input::eKeys::KB_MAX)];	// GLFWのキー一覧
};

} // namespace tkl

using eKeys = tkl::Input::eKeys;