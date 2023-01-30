#include"Input.h"
#include<cassert>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

void Input::Initialize(/*HINSTANCE hInstance, HWND hwnd*/WinApp*winApp)
{
	//借りてきたWinAppのインスタンスを記録
	this->winApp = winApp;
	HRESULT result;

	//IDirectInput8* directInput = nullptr;
	result = DirectInput8Create(/*hInstance*/winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));


	//IDirectInputDevice8* keyboard = nullptr;
	result = directInput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	assert(SUCCEEDED(result));

	//入力データ形式のセット
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(result));

	//排他制御レベルのセット
	result = devkeyboard->SetCooperativeLevel(/*hwnd*/winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

}
void Input::Update()
{
	HRESULT result;

	// キーボード情報の取得開始
	result = devkeyboard->Acquire();

	memcpy(keyPre, key, sizeof(key));

	// 全キーの入力状態を取得する
	result = devkeyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNumber)
{
	//指定キーを押していればtrueを返す
	if (key[keyNumber])
	{
		return true;
	}

	//そうでなければfalseを返す
	return false;
}

bool Input::TriggerKey(BYTE keyNumbe)
{
	if (key[keyNumbe] && !keyPre[keyNumbe])
	{
		return true;
	}
	return false;
}