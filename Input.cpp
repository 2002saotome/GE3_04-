#include"Input.h"
#include<cassert>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

void Input::Initialize(/*HINSTANCE hInstance, HWND hwnd*/WinApp*winApp)
{
	//�؂�Ă���WinApp�̃C���X�^���X���L�^
	this->winApp = winApp;
	HRESULT result;

	//IDirectInput8* directInput = nullptr;
	result = DirectInput8Create(/*hInstance*/winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));


	//IDirectInputDevice8* keyboard = nullptr;
	result = directInput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	assert(SUCCEEDED(result));

	//���̓f�[�^�`���̃Z�b�g
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(result));

	//�r�����䃌�x���̃Z�b�g
	result = devkeyboard->SetCooperativeLevel(/*hwnd*/winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

}
void Input::Update()
{
	HRESULT result;

	// �L�[�{�[�h���̎擾�J�n
	result = devkeyboard->Acquire();

	memcpy(keyPre, key, sizeof(key));

	// �S�L�[�̓��͏�Ԃ��擾����
	result = devkeyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNumber)
{
	//�w��L�[�������Ă����true��Ԃ�
	if (key[keyNumber])
	{
		return true;
	}

	//�����łȂ����false��Ԃ�
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