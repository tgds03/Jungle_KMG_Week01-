#include "stdafx.h"
#include "Framework/Core/CRenderer.h"
#include "Math\FVector.h"
#include "Math\FMatrix.h"
#include "UCubeComponent.h"
#include "UPlaneComponent.h"

const int TARGET_FPS = 60;
const double TARGET_FRAMERATE = 1000.0 / TARGET_FPS;

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
	Time::Instance()->Init();
	Input::Instance()->Init(hInstance, hWnd, 800, 600);
	GuiController* guiController = new GuiController(hWnd, CRenderer::Instance()->GetGraphics());


	UCubeComponent* obj = new UCubeComponent();
	UPlaneComponent* ground = new UPlaneComponent();

	MSG msg = {};
	while (msg.message != WM_QUIT) {
		Time::Instance()->_query_frame_update_time();
		Input::Instance()->Frame();
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		UActorComponent::UpdateAll();
		CRenderer::Instance()->GetGraphics()->RenderBegin();
		guiController->NewFrame();
		UActorComponent::RenderAll();
		guiController->RenderFrame();
		CRenderer::Instance()->GetGraphics()->RenderEnd();
		Time::Instance()->_query_frame_end_time();
		/*do {
			Sleep(0);
			Time::Instance()->_query_frame_end_time();
		} while ( Time::GetDeltaTime() < TARGET_FRAMERATE );*/
		
	}
	Input::Instance()->Shutdown();
	CRenderer::Release();
	return 0;
}