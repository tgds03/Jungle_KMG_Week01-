#include "stdafx.h"
#include "Framework/Core/CRenderer.h"
#include "Math\FVector.h"
#include "Math\FMatrix.h"
#include "UCubeComponent.h"

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
	WCHAR winTitleName[] = L"Title";

	WNDCLASS winClass = {};
	winClass.hInstance = hInstance;
	winClass.lpszClassName = winClassName;
	winClass.lpfnWndProc = WinProc;
	RegisterClass(&winClass);

	HWND hWnd = CreateWindow(winClassName, winTitleName, 
		WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		nullptr, nullptr, hInstance, nullptr
	);

	CRenderer::Instance()->Init(hWnd);
	UCubeComponent* obj = new UCubeComponent();

	MSG msg = {};
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		obj->RelativeRotation += FVector(0.01, 0.01, 0.02);
		CRenderer::Instance()->GetGraphics()->RenderBegin();
		UActorComponent::RenderAll();
		CRenderer::Instance()->GetGraphics()->RenderEnd();
	}
	return 0;
}