#include "stdafx.h"
#include "Input.h"

Input* Input::_instance = nullptr;

bool Input::Init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight) {
	HRESULT result;

	// Store the screen size which will be used for positioning the mouse cursor.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Initialize the location of the mouse on the screen.
	//m_mouseX = 0;
	//m_mouseY = 0;

	// Initialize the main direct input interface.
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	assert(SUCCEEDED(result));

	// Ű���� �ʱ�ȭ
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	assert(SUCCEEDED(result));
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(result));
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	assert(SUCCEEDED(result));
	result = m_keyboard->Acquire();
	assert(SUCCEEDED(result));

	// ���콺 �ʱ�ȭ
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	assert(SUCCEEDED(result));
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	assert(SUCCEEDED(result));
	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	assert(SUCCEEDED(result));
	result = m_mouse->Acquire();
	assert(SUCCEEDED(result));

	m_hWnd = hwnd;
	return true;
}

void Input::Shutdown() {
	// Release the mouse.
	if ( m_mouse ) {
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}
	// Release the keyboard.
	if ( m_keyboard ) {
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}
	// Release the main interface to direct input.
	if ( m_directInput ) {
		m_directInput->Release();
		m_directInput = 0;
	}
	return;
}

bool Input::Frame() {
	bool result;

	result = ReadKeyboard();
	if ( !result )
		return false;

	result = ReadMouse();
	if ( !result )
		return false;

	ProcessInput();

	return true;
}

bool Input::IsKeyDown(char keycode) {
	if ( m_keyboardState[keycode] & 0x80 )
		return true;
	return false;
}

bool Input::IsKeyPressed(char keycode) {
	if ( m_keyboardState[keycode] & 0x80 && !(m_keyboardStatePrevious[keycode] & 0x80) )
		return true;
	return false;
}

bool Input::IsKeyReleased(char keycode) {
	if ( !(m_keyboardState[keycode] & 0x80) && m_keyboardStatePrevious[keycode] & 0x80 )
		return true;
	return false;
}

bool Input::IsMouseButtonDown(char button) {
	if ( m_mouseState.rgbButtons[button] & 0x80 )
		return true;
	return false;
}

bool Input::IsMouseButtonPressed(char button) {
	if ( m_mouseState.rgbButtons[button] & 0x80 && !(m_mouseStatePrevious.rgbButtons[button] & 0x80) )
		return true;
	return false;
}

bool Input::IsMouseButtonReleased(char button) {
	if ( !(m_mouseState.rgbButtons[button] & 0x80) && m_mouseStatePrevious.rgbButtons[button] & 0x80 )
		return true;
	return false;
}

void Input::GetMouseLocation(int& mouse_x, int& mouse_y) {
	//mouseX = m_mouseX;
	//mouseY = m_mouseY;
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(m_hWnd, &p);
	mouse_x = p.x;
	mouse_y = p.y;
	return;
}

void Input::GetMouseDelta(int& mouse_x, int& mouse_y) {
	mouse_x = m_mouseState.lX;
	mouse_y = m_mouseState.lY;
}



bool Input::ReadKeyboard() {
	HRESULT result;

	memcpy(m_keyboardStatePrevious, m_keyboardState, sizeof(m_keyboardState));
	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if ( FAILED(result) ) {
		if ( (result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED) ) {
			m_keyboard->Acquire();
		} else {
			return false;
		}
	}

	return true;
}

bool Input::ReadMouse() {
	HRESULT result;

	memcpy(&m_mouseStatePrevious, &m_mouseState, sizeof(DIMOUSESTATE));
	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if ( FAILED(result) ) {
		// If the mouse lost focus or was not acquired then try to get control back.
		if ( (result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED) ) {
			m_mouse->Acquire();
		} else {
			return false;
		}
	}
	return true;
}

void Input::ProcessInput() {

	//m_mouseX += m_mouseState.lX;
	//m_mouseY += m_mouseState.lY;

	//if ( m_mouseX < 0 ) { m_mouseX = 0; }
	//if ( m_mouseY < 0 ) { m_mouseY = 0; }

	//if ( m_mouseX > m_screenWidth ) { m_mouseX = m_screenWidth; }
	//if ( m_mouseY > m_screenHeight ) { m_mouseY = m_screenHeight; }

	return;
}
//void Input::GetMouseRay(FVector& rayOrigin, FVector& rayDirection,
//	const FMatrix& viewMatrix, const FMatrix& projectionMatrix) {
//	POINT cursorPos;
//	GetCursorPos(&cursorPos);
//	ScreenToClient(m_hWnd, &cursorPos);
//
//	float ndcX = ((float)cursorPos.x / m_screenWidth) * 2.0f - 1.0f;
//	float ndcY = 1.0f - ((float)cursorPos.y / m_screenHeight) * 2.0f;
//
//	// **���� ���������� ���� ������ �׻� ī�޶��� ���� �����̾�� ��**
//	FMatrix invView = XMMatrixInverse(nullptr, viewMatrix);
//	FVector forward;
//	XMStoreFloat3(&forward, invView.r[2]); // Z�� ���� (ī�޶��� ���� ����)
//
//	rayDirection = forward; // **���� ���������� ������ �׻� ����**
//
//	// **���� ���������� ���� �������� ���콺 Ŭ�� ��ġ���� ��ȯ�ؾ� ��**
//	FMatrix invProj = XMMatrixInverse(nullptr, projectionMatrix);
//	FVector rayClip = XMVectorSet(ndcX, ndcY, 0.0f, 1.0f); // z=0���� ����
//	FVector rayWorld = XMVector4Transform(rayClip, invProj);
//	rayWorld = XMVector4Transform(rayWorld, invView);
//
//	XMStoreFloat3(&rayOrigin, rayWorld); // ���콺 ��ġ�� `rayOrigin`���� ����
//}
