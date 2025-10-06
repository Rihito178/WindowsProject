#include "Input.h"


//HWND hwnd = nullptr;


namespace Input
{
	//キーボードインプット
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE keyState[256] = { 0 };        //今回のフレームでの各キーの状態
	BYTE prevKeyState[256] = { 0 };    //前フレームでの各キーの状態
	
	//マウスインプット
	LPDIRECTINPUTDEVICE8 pMouseDevice = nullptr;
	DIMOUSESTATE mouseState; //マウスの状態
	DIMOUSESTATE prevMouseState;

	XMVECTOR mousePosition;

	
};

	void Input::Initialize(HWND hwnd)
	{
		//キーボード
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	
	
		//マウス
		pDInput->CreateDevice(GUID_SysMouse, &pMouseDevice, nullptr);
		pMouseDevice->SetDataFormat(&c_dfDIMouse);
		pMouseDevice->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	}

	void Input::Update()
	{
		//キーボード
		memcpy(prevKeyState, keyState, sizeof(keyState));
		for (auto i = 0;i < 256;i++) 
		{
			prevKeyState[i] = keyState[i]; //前回の状態を保存
		}
		pKeyDevice->Acquire(); 
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState); 
	
	
		//マウス
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
		//前回押した
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
		//今回押した
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
