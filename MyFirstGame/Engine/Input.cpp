#include "Input.h"


//HWND hwnd = nullptr;


namespace Input
{
	//�L�[�{�[�h�C���v�b�g
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE keyState[256] = { 0 };        //����̃t���[���ł̊e�L�[�̏��
	BYTE prevKeyState[256] = { 0 };    //�O�t���[���ł̊e�L�[�̏��
	
	//�}�E�X�C���v�b�g
	LPDIRECTINPUTDEVICE8 pMouseDevice = nullptr;
	DIMOUSESTATE mouseState; //�}�E�X�̏��
	DIMOUSESTATE prevMouseState;

	XMVECTOR mousePosition;

	
};

	void Input::Initialize(HWND hwnd)
	{
		//�L�[�{�[�h
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	
	
		//�}�E�X
		pDInput->CreateDevice(GUID_SysMouse, &pMouseDevice, nullptr);
		pMouseDevice->SetDataFormat(&c_dfDIMouse);
		pMouseDevice->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	}

	void Input::Update()
	{
		//�L�[�{�[�h
		memcpy(prevKeyState, keyState, sizeof(keyState));
		for (auto i = 0;i < 256;i++) 
		{
			prevKeyState[i] = keyState[i]; //�O��̏�Ԃ�ۑ�
		}
		pKeyDevice->Acquire(); 
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState); 
	
	
		//�}�E�X
		pMouseDevice->Acquire();
		memcpy(&prevMouseState, &mouseState, sizeof(mouseState));
		pMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);
		

	}



	bool Input::IsKey(int keyCode)
	{

		if (keyState[keyCode] &0x80)
		{
			return true;
		}
		return false;
	}


	bool Input::IsMouseButton(int btnCode)
	{
		if (mouseState.rgbButtons[btnCode] & 0x80)
		{
			return true;
		}
		return false;
	}





	bool Input::IsKeyUp(int keyCode)
	{
		//�O�񉟂���
		if (!IsKey(keyCode) && prevKeyState[keyCode] & 0x80)
		{

			return true;
		}
		return false;
	}

	bool Input::IsMouseButtonUP(int btnCode)
	{
		return false;
	}




	bool Input::IsKeyDown(int keyCode)
	{
		//���񉟂���
		if (!IsKey(keyCode) && prevKeyState[keyCode] & 0x80)
		{

			return true;
		}
		return false;
	}


	bool Input::IsMouseButtonDown(int btnCode)
	{
		return false;
	}




	XMVECTOR Input::GetMousePosition()
	{
		return mousePosition;
	}


	void Input::SetMousePosition(int x, int y)
	{
		mousePosition = XMVectorSet((float)x, (float)y, 0.0f, 1.0f);
	}




	void Input::Release()
	{
		SAFE_RELEASE(pDInput);
	}
