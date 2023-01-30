#include "WinApp.h"
#pragma comment(lib,"winmm.lib")
#include<Windows.h>
void WinApp::Initialize()
{

	// ウィンドウサイズ
	//const int window_width = 1280;  // 横幅
	//const int window_height = 720;  // 縦幅
	// ウィンドウクラスの設定
	//WNDCLASSEX w{};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc; // ウィンドウプロシージャを設定
	w.lpszClassName = L"DirectXGame"; // ウィンドウクラス名
	w.hInstance = GetModuleHandle(nullptr); // ウィンドウハンドル
	w.hCursor = LoadCursor(NULL, IDC_ARROW); // カーソル指定
	// ウィンドウクラスをOSに登録する
	RegisterClassEx(&w);
	// ウィンドウサイズ{ X座標 Y座標 横幅 縦幅 }
	RECT wrc = { 0, 0, window_width, window_height };
	// 自動でサイズを補正する
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);
	// ウィンドウオブジェクトの生成
	/*HWND*/ hwnd = CreateWindow(w.lpszClassName, // クラス名
		L"DirectXGame",         // タイトルバーの文字
		WS_OVERLAPPEDWINDOW,        // 標準的なウィンドウスタイル
		CW_USEDEFAULT,              // 表示X座標（OSに任せる）
		CW_USEDEFAULT,              // 表示Y座標（OSに任せる）
		wrc.right - wrc.left,       // ウィンドウ横幅
		wrc.bottom - wrc.top,   // ウィンドウ縦幅
		nullptr,                // 親ウィンドウハンドル
		nullptr,                // メニューハンドル
		w.hInstance,            // 呼び出しアプリケーションハンドル
		nullptr);               // オプション

	// ウィンドウを表示状態にする
	ShowWindow(hwnd, SW_SHOW);

	//システムタイマーの分解能を上げる
	timeBeginPeriod(1);
}
void WinApp::Update()
{

}
void WinApp::Finalize()
{
	//ウィンドウクラスを登録解除
	UnregisterClass(w.lpszClassName, w.hInstance);
}
bool WinApp::ProcessMessage()
{
	MSG msg{};
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (msg.message == WM_QUIT)
	{
		return true;
	}
	return false;
}
LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//メッセージで分岐
	switch (msg)
	{
		//ウィンドウが破棄された
	case WM_DESTROY:
		//OSに対して、アプリの終了を伝える
		PostQuitMessage(0);
		return 0;
	}
	//標準の処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}