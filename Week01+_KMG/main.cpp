#include "stdafx.h"
#include "Framework/Core/CRenderer.h"
#include "Math\FVector.h"
#include "Math\FMatrix.h"

double gFrameElapsedTime = 0; // milisecond

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WCHAR winClassName[] = L"WindowClass";
	WCHAR winTitleName[] = L"My Engine";

	WNDCLASS winClass = {};
	winClass.hInstance = hInstance;
	winClass.lpszClassName = winClassName;
	winClass.lpfnWndProc = WinProc;
	RegisterClass(&winClass);

	HWND hWnd = CreateWindow(winClassName, winTitleName, 
		WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080,
		nullptr, nullptr, hInstance, nullptr
	);

	const int TARGET_FPS = 60;
	const double TARGET_FRAMETIME = 1000.0 / TARGET_FPS;
	LARGE_INTEGER frequency, frameStartTime, frameUpdateTime, frameEndTime;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceFrequency(&frameStartTime);

	CRenderer::Instance()->Init(hWnd);
	MSG msg = {};
	while (msg.message != WM_QUIT) 
	{
		QueryPerformanceFrequency(&frameUpdateTime);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		CRenderer::Instance()->GetGraphics()->RenderBegin();
		
		CRenderer::Instance()->GetGraphics()->RenderEnd();

		do {
			Sleep(0);
			QueryPerformanceCounter(&frameEndTime);
			gFrameElapsedTime = (frameEndTime.QuadPart - frameUpdateTime.QuadPart) * 1000.0 / frequency.QuadPart;
		}
	}
	return 0;
}