#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>

namespace tkl
{
class Input
{
public:

	// �L�[�{�[�h�Ή��ꗗ
	enum class eKeys
	{
		KB_ENTER,	// �G���^�[
		KB_LSHIFT,	// ���V�t�g
		KB_RSHIFT,	// �E�V�t�g
		KB_SPACE,	// �X�y�[�X
		KB_LEFT,	// ���(��)
		KB_UP,		// ���(��)
		KB_RIGHT,	// ���(�E)
		KB_DOWN,	// ���(��)

		// �A���t�@�x�b�g
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

		// ����
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

	// �������ςȂ����m(�����L�[���Ή�)
	template<typename eKeys>
	static bool IsKeyDown(eKeys keys){
		return sKeyDownStatus[static_cast<int>(keys)];
	}

	// 1�t���[���������m(�����L�[���Ή�)
	template<typename eKeys>
	static bool IsKeyDownTrigger(eKeys keys){
		return sKeyDownTrgStatus[static_cast<int>(keys)];
	}

private:
	Input(){}

	static void InputKeyboard(GLFWwindow* const);

private:
	static bool sKeyDownStatus[static_cast<int>(Input::eKeys::KB_MAX)];		// �L�[�������
	static bool sPrevKeyDownStatus[static_cast<int>(Input::eKeys::KB_MAX)];	// �O��̃L�[�������
	static bool sKeyDownTrgStatus[static_cast<int>(Input::eKeys::KB_MAX)];	// �L�[�����g���K�[���
	static unsigned short sKeys[static_cast<int>(Input::eKeys::KB_MAX)];	// GLFW�̃L�[�ꗗ
};

} // namespace tkl

using eKeys = tkl::Input::eKeys;