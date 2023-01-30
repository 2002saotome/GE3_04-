#include<windows.h>
#pragma once
class WinApp
{
public:
	//getter
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return w.hInstance; }
private:
	//ウィンドウクラスの設定
	WNDCLASSEX w{};
	//ウィンドウハンドル
	HWND hwnd = nullptr;
//静的メンバ関数
public:
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
//メンバ関数
public:
	//初期化
	void Initialize();
	//更新
	void Update();
	//終了
	void Finalize();
	//メッセージの処理
	bool ProcessMessage();
//定数
public:
	//ウィンドウ横幅
	static const int window_width = 1280;
	//ウィンドウ縦幅
	static const int window_height = 720;
};

