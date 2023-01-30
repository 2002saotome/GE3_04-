#include<windows.h>
#pragma once
class WinApp
{
public:
	//getter
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return w.hInstance; }
private:
	//�E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX w{};
	//�E�B���h�E�n���h��
	HWND hwnd = nullptr;
//�ÓI�����o�֐�
public:
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
//�����o�֐�
public:
	//������
	void Initialize();
	//�X�V
	void Update();
	//�I��
	void Finalize();
	//���b�Z�[�W�̏���
	bool ProcessMessage();
//�萔
public:
	//�E�B���h�E����
	static const int window_width = 1280;
	//�E�B���h�E�c��
	static const int window_height = 720;
};

