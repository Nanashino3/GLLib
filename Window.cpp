
#include "Window.h"
#include <iostream>

//********************************************************
// 関数名：Window
// 概　要：コンストラクタ
// 引　数：なし
Window::Window(int width, int height, const char* title)
: mWindow(glfwCreateWindow(width, height, title, 0, 0))
, mScale(100.0f)
{
	if (mWindow == 0) {
		std::cerr << "Can't create GLFW window." << std::endl;
		exit(1);
	}
	// 現在のウィンドウを処理対象にする
	glfwMakeContextCurrent(mWindow);

	// GLEWを初期化する
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Can't initialize GLEW" << std::endl;
		exit(1);
	}

	// 垂直同期のタイミングを待つ
	glfwSwapInterval(1);

	// thisポインタを記録しておく
	glfwSetWindowUserPointer(mWindow, this);

	// ウィンドウサイズの変更時に呼び出す処理の登録
	glfwSetWindowSizeCallback(mWindow, Resize);

	Resize(mWindow, width, height);
}

//********************************************************
// 関数名：~Window
// 概　要：デストラクタ
// 引　数：なし
Window::~Window()
{
	glfwDestroyWindow(mWindow);
}

bool Window::IsWindowShouldClose() const
{
	return glfwWindowShouldClose(mWindow);
}

//********************************************************
// 関数名：SwapBuffers
// 概　要：シェーダオブジェクトのロード(2D用)
// 引　数：第1引数[IN]　頂点シェーダのファイル名
// 　　　　第2引数[IN]　画素シェーダのファイル名
void Window::SwapBuffers() const
{
	// カラーバッファを入れ替える
	glfwSwapBuffers(mWindow);

	// イベントを取り出す
	glfwPollEvents();
}


void Window::Resize(GLFWwindow* const window, int width, int height)
{
	// フレームバッファサイズを確認
	int frameBufWidth, frameBufHeight;
	glfwGetFramebufferSize(window, &frameBufWidth, &frameBufHeight);

	// フレームバッファ全体をビューポートに設定
	glViewport(0, 0, frameBufWidth, frameBufHeight);

	Window* const instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if(instance != 0){
		instance->mWindowSize[0] = static_cast<GLfloat>(width);
		instance->mWindowSize[1] = static_cast<GLfloat>(height);
	}
}